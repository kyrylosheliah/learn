/*
 * Copyright 2020 Google LLC. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.google.mlkit.vision.markup;

import static java.lang.Math.max;
import static java.lang.Math.min;

import android.app.ActivityManager;
import android.app.ActivityManager.MemoryInfo;
import android.content.Context;
import android.graphics.Bitmap;
import android.os.SystemClock;
import android.util.Log;
import android.widget.Toast;
import androidx.annotation.GuardedBy;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.google.android.gms.tasks.Task;
import com.google.android.gms.tasks.TaskExecutors;
import com.google.android.gms.tasks.Tasks;
import com.google.android.odml.image.BitmapMlImageBuilder;
import com.google.android.odml.image.ByteBufferMlImageBuilder;
import com.google.android.odml.image.MlImage;
import com.google.mlkit.common.MlKitException;
import com.google.mlkit.vision.common.InputImage;
import com.google.mlkit.vision.markup.util.BitmapUtils;
import com.google.mlkit.vision.markup.util.PreferenceUtils;
import java.nio.ByteBuffer;
import java.util.Timer;
import java.util.TimerTask;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;

import java.util.concurrent.Executor;
import java.util.concurrent.atomic.AtomicBoolean;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;

import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;

import com.google.mlkit.vision.markup.GraphicOverlay.Graphic;



/**
 * Abstract base class for vision frame processors. Subclasses need to implement {@link
 * #onSuccess(Object, GraphicOverlay)} to define what they want to with the detection results and
 * {@link #detectInImage(InputImage)} to specify the detector object.
 *
 * @param <T> The type of the detected feature.
 */
public abstract class VisionProcessorBase<T> implements VisionImageProcessor {

  protected static final String MANUAL_TESTING_LOG = "LogTagForTest";
  private static final String TAG = "VisionProcessorBase";

  private final ActivityManager activityManager;
  private final Timer fpsTimer = new Timer();
  private final ScopedExecutor executor;
  private final TemperatureMonitor temperatureMonitor;

  // Whether this processor is already shut down
  private boolean isShutdown;

  // Used to calculate latency, running in the same thread, no sync needed.
  private int numRuns = 0;
  private long totalFrameMs = 0;
  private long maxFrameMs = 0;
  private long minFrameMs = Long.MAX_VALUE;
  private long totalDetectorMs = 0;
  private long maxDetectorMs = 0;
  private long minDetectorMs = Long.MAX_VALUE;

  // Frame count that have been processed so far in an one second interval to calculate FPS.
  private int frameProcessedInOneSecondInterval = 0;
  private int framesPerSecond = 0;

  public boolean markupFlag = false;

  // To keep the latest images and its metadata.
  @GuardedBy("this")
  private ByteBuffer latestImage;

  @GuardedBy("this")
  private FrameMetadata latestImageMetaData;
  // To keep the images and metadata in process.
  @GuardedBy("this")
  private ByteBuffer processingImage;

  @GuardedBy("this")
  private FrameMetadata processingMetaData;

  protected VisionProcessorBase(Context context) {
    activityManager = (ActivityManager) context.getSystemService(Context.ACTIVITY_SERVICE);
    executor = new ScopedExecutor(TaskExecutors.MAIN_THREAD);
    fpsTimer.scheduleAtFixedRate(
        new TimerTask() {
          @Override
          public void run() {
            framesPerSecond = frameProcessedInOneSecondInterval;
            frameProcessedInOneSecondInterval = 0;
          }
        },
        /* delay= */ 0,
        /* period= */ 1000);
    temperatureMonitor = new TemperatureMonitor(context);
  }

  // -----------------Code for processing single still image----------------------------------------
  @Override
  public void processBitmap(Bitmap bitmap, final GraphicOverlay graphicOverlay) {
    long frameStartMs = SystemClock.elapsedRealtime();

    if (isMlImageEnabled(graphicOverlay.getContext())) {
      MlImage mlImage = new BitmapMlImageBuilder(bitmap).build();
      requestDetectInImage(
              mlImage,
              graphicOverlay,
              /* originalCameraImage= */ null,
              /* shouldShowFps= */ false,
              frameStartMs);
      mlImage.close();
    } else {
      requestDetectInImage(
              InputImage.fromBitmap(bitmap, 0),
              graphicOverlay,
              /* originalCameraImage= */ null,
              /* shouldShowFps= */ false,
              frameStartMs);
    }
  }

  // -----------------Code for processing live preview frame from Camera1 API-----------------------
  @Override
  public synchronized void processByteBuffer(
      ByteBuffer data, final FrameMetadata frameMetadata, final GraphicOverlay graphicOverlay) {
    latestImage = data;
    latestImageMetaData = frameMetadata;
    if (processingImage == null && processingMetaData == null) {
      processLatestImage(graphicOverlay);
    }
  }

  private synchronized void processLatestImage(final GraphicOverlay graphicOverlay) {
    processingImage = latestImage;
    processingMetaData = latestImageMetaData;
    latestImage = null;
    latestImageMetaData = null;
    if (processingImage != null && processingMetaData != null && !isShutdown) {
      processImage(processingImage, processingMetaData, graphicOverlay);
    }
  }

  private void processImage(
      ByteBuffer data, final FrameMetadata frameMetadata, final GraphicOverlay graphicOverlay) {
    long frameStartMs = SystemClock.elapsedRealtime();

    // If live viewport is on (that is the underneath surface view takes care of the camera preview
    // drawing), skip the unnecessary bitmap creation that used for the manual preview drawing.
    Bitmap bitmap =
        PreferenceUtils.isCameraLiveViewportEnabled(graphicOverlay.getContext())
            ? null
            : BitmapUtils.getBitmap(data, frameMetadata);

    if (isMlImageEnabled(graphicOverlay.getContext())) {
      MlImage mlImage =
          new ByteBufferMlImageBuilder(
                  data,
                  frameMetadata.width,
                  frameMetadata.height,
                  MlImage.IMAGE_FORMAT_NV21)
              .setRotation(frameMetadata.rotation)
              .build();

      requestDetectInImage(mlImage, graphicOverlay, bitmap, /* shouldShowFps= */ true, frameStartMs)
          .addOnSuccessListener(executor, results -> processLatestImage(graphicOverlay));

      // This is optional. Java Garbage collection can also close it eventually.
      mlImage.close();
      return;
    }

    requestDetectInImage(
            InputImage.fromByteBuffer(
                data,
                frameMetadata.width,
                frameMetadata.height,
                frameMetadata.rotation,
                InputImage.IMAGE_FORMAT_NV21),
            graphicOverlay,
            bitmap,
            /* shouldShowFps= */ true,
            frameStartMs)
        .addOnSuccessListener(executor, results -> processLatestImage(graphicOverlay));
  }

  // -----------------Common processing logic-------------------------------------------------------
  private Task<T> requestDetectInImage(
      final InputImage image,
      final GraphicOverlay graphicOverlay,
      @Nullable final Bitmap originalCameraImage,
      boolean shouldShowFps,
      long frameStartMs) {
    return setUpListener(
        detectInImage(image), graphicOverlay, originalCameraImage, shouldShowFps, frameStartMs);
  }

  private Task<T> requestDetectInImage(
      final MlImage image,
      final GraphicOverlay graphicOverlay,
      @Nullable final Bitmap originalCameraImage,
      boolean shouldShowFps,
      long frameStartMs) {
    return setUpListener(
        detectInImage(image), graphicOverlay, originalCameraImage, shouldShowFps, frameStartMs);
  }

  private Task<T> setUpListener(
      Task<T> task,
      final GraphicOverlay graphicOverlay,
      @Nullable final Bitmap originalCameraImage,
      boolean shouldShowFps,
      long frameStartMs) {
    final long detectorStartMs = SystemClock.elapsedRealtime();
    return task.addOnSuccessListener(
            executor,
            results -> {
              long endMs = SystemClock.elapsedRealtime();
              long currentFrameLatencyMs = endMs - frameStartMs;
              long currentDetectorLatencyMs = endMs - detectorStartMs;
              if (numRuns >= 500) {
                resetLatencyStats();
              }
              numRuns++;
              frameProcessedInOneSecondInterval++;
              totalFrameMs += currentFrameLatencyMs;
              maxFrameMs = max(currentFrameLatencyMs, maxFrameMs);
              minFrameMs = min(currentFrameLatencyMs, minFrameMs);
              totalDetectorMs += currentDetectorLatencyMs;
              maxDetectorMs = max(currentDetectorLatencyMs, maxDetectorMs);
              minDetectorMs = min(currentDetectorLatencyMs, minDetectorMs);

              // Only log inference info once per second. When frameProcessedInOneSecondInterval is
              // equal to 1, it means this is the first frame processed during the current second.
              if (frameProcessedInOneSecondInterval == 1) {
                Log.d(TAG, "Num of Runs: " + numRuns);
                Log.d(
                    TAG,
                    "Frame latency: max="
                        + maxFrameMs
                        + ", min="
                        + minFrameMs
                        + ", avg="
                        + totalFrameMs / numRuns);
                Log.d(
                    TAG,
                    "Detector latency: max="
                        + maxDetectorMs
                        + ", min="
                        + minDetectorMs
                        + ", avg="
                        + totalDetectorMs / numRuns);
                MemoryInfo mi = new MemoryInfo();
                activityManager.getMemoryInfo(mi);
                long availableMegs = mi.availMem / 0x100000L;
                Log.d(TAG, "Memory available in system: " + availableMegs + " MB");
                temperatureMonitor.logTemperature();
              }

              graphicOverlay.clear();
              if (originalCameraImage != null) {
                graphicOverlay.add(new CameraImageGraphic(graphicOverlay, originalCameraImage));
              }
              VisionProcessorBase.this.onSuccess(results, graphicOverlay);
              if (!PreferenceUtils.shouldHideDetectionInfo(graphicOverlay.getContext())) {
                graphicOverlay.add(
                    new InferenceInfoGraphic(
                        graphicOverlay,
                        currentFrameLatencyMs,
                        currentDetectorLatencyMs,
                        shouldShowFps ? framesPerSecond : null));
              }
              graphicOverlay.postInvalidate();
            })
        .addOnFailureListener(
            executor,
            e -> {
              graphicOverlay.clear();
              graphicOverlay.postInvalidate();
              String error = "Failed to process. Error: " + e.getLocalizedMessage();
              Toast.makeText(
                      graphicOverlay.getContext(),
                      error + "\nCause: " + e.getCause(),
                      Toast.LENGTH_SHORT)
                  .show();
              Log.d(TAG, error);
              e.printStackTrace();
              VisionProcessorBase.this.onFailure(e);
            });
  }

  @Override
  public void stop() {
    executor.shutdown();
    isShutdown = true;
    resetLatencyStats();
    fpsTimer.cancel();
    temperatureMonitor.stop();
  }

  private void resetLatencyStats() {
    numRuns = 0;
    totalFrameMs = 0;
    maxFrameMs = 0;
    minFrameMs = Long.MAX_VALUE;
    totalDetectorMs = 0;
    maxDetectorMs = 0;
    minDetectorMs = Long.MAX_VALUE;
  }

  protected abstract Task<T> detectInImage(InputImage image);

  protected Task<T> detectInImage(MlImage image) {
    return Tasks.forException(
        new MlKitException(
            "MlImage is currently not demonstrated for this feature",
            MlKitException.INVALID_ARGUMENT));
  }

  protected abstract void onSuccess(@NonNull T results, @NonNull GraphicOverlay graphicOverlay);

  protected abstract void onFailure(@NonNull Exception e);

  protected boolean isMlImageEnabled(Context context) {
    return false;
  }






  /** Draw camera image to background. */
  private final class CameraImageGraphic extends Graphic {

    private final Bitmap bitmap;

    public CameraImageGraphic(GraphicOverlay overlay, Bitmap bitmap) {
      super(overlay);
      this.bitmap = bitmap;
    }

    @Override
    public void draw(Canvas canvas) {
      canvas.drawBitmap(bitmap, getTransformationMatrix(), null);
    }
  }


  /**
   * Monitors device temperature.
   */
  private final class TemperatureMonitor implements SensorEventListener {

    private static final String TAG = "TemperatureMonitor";

    public Map<String, Float> sensorReadingsCelsius = new HashMap<>();

    private final SensorManager sensorManager;

    public TemperatureMonitor(Context context) {
      sensorManager = (SensorManager) context.getSystemService(Context.SENSOR_SERVICE);
      List<Sensor> allSensors = sensorManager.getSensorList(Sensor.TYPE_ALL);
      for (Sensor sensor : allSensors) {
        // Assumes sensors with "temperature" substring in their names are temperature sensors.
        // Those sensors may measure the temperature of different parts of the device. It makes more
        // sense to track the change of themselves, e.g. compare the reading before and after running
        // a detector for a certain amount of time, rather than relying on their absolute values at a
        // certain time.
        if (sensor.getName().toLowerCase().contains("temperature")) {
          sensorManager.registerListener(this, sensor, SensorManager.SENSOR_DELAY_NORMAL);
        }
      }
    }

    public void stop() {
      sensorManager.unregisterListener(this);
    }

    public void logTemperature() {
      for (Map.Entry<String, Float> entry : sensorReadingsCelsius.entrySet()) {
        float tempC = entry.getValue();
        // Skips likely invalid sensor readings
        if (tempC < 0) {
          continue;
        }
        float tempF = tempC * 1.8f + 32f;
        Log.i(TAG, String.format(Locale.US, "%s:\t%.1fC\t%.1fF", entry.getKey(), tempC, tempF));
      }
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {}

    @Override
    public void onSensorChanged(SensorEvent sensorEvent) {
      sensorReadingsCelsius.put(sensorEvent.sensor.getName(), sensorEvent.values[0]);
    }
  }

  /**
   * Wraps an existing executor to provide a {@link #shutdown} method that allows subsequent
   * cancellation of submitted runnables.
   */
  private final class ScopedExecutor implements Executor {

    private final Executor executor;
    private final AtomicBoolean shutdown = new AtomicBoolean();

    public ScopedExecutor(@NonNull Executor executor) {
      this.executor = executor;
    }

    @Override
    public void execute(@NonNull Runnable command) {
      // Return early if this object has been shut down.
      if (shutdown.get()) {
        return;
      }
      executor.execute(
              () -> {
                // Check again in case it has been shut down in the mean time.
                if (shutdown.get()) {
                  return;
                }
                command.run();
              });
    }

    /**
     * After this method is called, no runnables that have been submitted or are subsequently
     * submitted will start to execute, turning this executor into a no-op.
     *
     * <p>Runnables that have already started to execute will continue.
     */
    public void shutdown() {
      shutdown.set(true);
    }
  }


  /** Graphic instance for rendering inference info (latency, FPS, resolution) in an overlay view. */
  private final class InferenceInfoGraphic extends GraphicOverlay.Graphic {

    private static final int TEXT_COLOR = Color.WHITE;
    private static final float TEXT_SIZE = 60.0f;

    private final Paint textPaint;
    private final GraphicOverlay overlay;
    private final long detectorLatency;

    // Only valid when a stream of input images is being processed. Null for single image mode.
    @Nullable private final Integer framesPerSecond;
    private boolean showLatencyInfo = true;

    public InferenceInfoGraphic(
            GraphicOverlay overlay,
            long frameLatency,
            long detectorLatency,
            @Nullable Integer framesPerSecond) {
      super(overlay);
      this.overlay = overlay;
      this.detectorLatency = detectorLatency;
      this.framesPerSecond = framesPerSecond;
      textPaint = new Paint();
      textPaint.setColor(TEXT_COLOR);
      textPaint.setTextSize(TEXT_SIZE);
      textPaint.setShadowLayer(5.0f, 0f, 0f, Color.BLACK);
      postInvalidate();
    }

    @Override
    public synchronized void draw(Canvas canvas) {
      if (!showLatencyInfo) {
        return;
      }
      // Draw FPS (if valid) and inference latency
      String toDraw = "";
      if (framesPerSecond != null) {
        toDraw = "FPS: " + framesPerSecond + " | ";
      }
      toDraw = toDraw + "Detector: " + detectorLatency + " ms";
      canvas.drawText(toDraw, TEXT_SIZE * 0.5f, TEXT_SIZE * 1.5f, textPaint);
    }
  }
}
