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

package com.google.mlkit.vision.markup.activity;

import android.content.Intent;
import android.os.Bundle;
import androidx.appcompat.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ArrayAdapter;
import android.widget.CompoundButton;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.Spinner;
import android.widget.Toast;
import android.widget.ToggleButton;
import com.google.android.gms.common.annotation.KeepName;
import com.google.mlkit.vision.markup.CameraSource;
import com.google.mlkit.vision.markup.CameraSourcePreview;
import com.google.mlkit.vision.markup.GraphicOverlay;
import com.google.mlkit.vision.markup.R;
import com.google.mlkit.vision.markup.TextRecognitionProcessor;
import com.google.mlkit.vision.markup.activity.SettingsActivity;
import com.google.mlkit.vision.text.chinese.ChineseTextRecognizerOptions;
import com.google.mlkit.vision.text.devanagari.DevanagariTextRecognizerOptions;
import com.google.mlkit.vision.text.japanese.JapaneseTextRecognizerOptions;
import com.google.mlkit.vision.text.korean.KoreanTextRecognizerOptions;
import com.google.mlkit.vision.text.latin.TextRecognizerOptions;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/** Live preview demo for ML Kit APIs. */
@KeepName
public final class LivePreviewActivity extends AppCompatActivity
    implements OnItemSelectedListener {
  private static final String TEXT_RECOGNITION_LATIN = "Text Recognition Latin";
  private static final String TEXT_RECOGNITION_CHINESE = "Text Recognition Chinese";
  private static final String TEXT_RECOGNITION_DEVANAGARI = "Text Recognition 21";
  private static final String TEXT_RECOGNITION_JAPANESE = "Text Recognition Japanese";
  private static final String TEXT_RECOGNITION_KOREAN = "Text Recognition Korean";

  private static final String TAG = "LivePreviewActivity";

  private boolean isRearCameraChecked = true;
  private CameraSource cameraSource = null;
  private CameraSourcePreview preview;
  private GraphicOverlay graphicOverlay;
  private String selectedModel = TEXT_RECOGNITION_LATIN;

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    Log.d(TAG, "onCreate");

    setContentView(R.layout.activity_vision_live_preview);

    preview = findViewById(R.id.preview_view);
    if (preview == null) {
      Log.d(TAG, "Preview is null");
    }
    graphicOverlay = findViewById(R.id.graphic_overlay);
    if (graphicOverlay == null) {
      Log.d(TAG, "graphicOverlay is null");
    }

    Spinner spinner = findViewById(R.id.spinner);
    List<String> options = new ArrayList<>();
    options.add(TEXT_RECOGNITION_LATIN);
    options.add(TEXT_RECOGNITION_CHINESE);
    options.add(TEXT_RECOGNITION_DEVANAGARI);
    options.add(TEXT_RECOGNITION_JAPANESE);
    options.add(TEXT_RECOGNITION_KOREAN);

    // Creating adapter for spinner
    ArrayAdapter<String> dataAdapter = new ArrayAdapter<>(this, R.layout.spinner_style, options);
    // Drop down layout style - list view with radio button
    dataAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
    // attaching data adapter to spinner
    spinner.setAdapter(dataAdapter);
    spinner.setOnItemSelectedListener(this);

    ImageButton facingSwitch = findViewById(R.id.facing_switch);
    facingSwitch.setOnClickListener((view) -> {
        Log.d(TAG, "Set facing");
        if (cameraSource != null) {
          if (isRearCameraChecked) {
            cameraSource.setFacing(CameraSource.CAMERA_FACING_FRONT);
            facingSwitch.setImageResource(R.drawable.ic_baseline_camera_front_24dp);
            isRearCameraChecked = false;
          } else {
            cameraSource.setFacing(CameraSource.CAMERA_FACING_BACK);
            facingSwitch.setImageResource(R.drawable.ic_baseline_camera_rear_24dp);
            isRearCameraChecked = true;
          }
        }
        preview.stop();
        startCameraSource();
    });

    ImageView settingsButton = findViewById(R.id.settings_button);
    settingsButton.setOnClickListener(
        v -> {
          Intent intent = new Intent(getApplicationContext(), SettingsActivity.class);
          intent.putExtra(
              SettingsActivity.EXTRA_LAUNCH_SOURCE, SettingsActivity.LaunchSource.LIVE_PREVIEW);
          startActivity(intent);
        });

    createCameraSource(selectedModel);
  }

  @Override
  public synchronized void onItemSelected(AdapterView<?> parent, View view, int pos, long id) {
    // An item was selected. You can retrieve the selected item using
    // parent.getItemAtPosition(pos)
    selectedModel = parent.getItemAtPosition(pos).toString();
    Log.d(TAG, "Selected model: " + selectedModel);
    preview.stop();
    createCameraSource(selectedModel);
    startCameraSource();
  }

  @Override
  public void onNothingSelected(AdapterView<?> parent) {
    // Do nothing.
  }

  private void createCameraSource(String model) {
    // If there's no existing cameraSource, create one.
    if (cameraSource == null) {
      cameraSource = new CameraSource(this, graphicOverlay);
    }

    try {
      switch (model) {
        case TEXT_RECOGNITION_LATIN:
          cameraSource.setMachineLearningFrameProcessor(
              new TextRecognitionProcessor(
                  this, new TextRecognizerOptions.Builder().build()));
          break;
        case TEXT_RECOGNITION_CHINESE:
          cameraSource.setMachineLearningFrameProcessor(
              new TextRecognitionProcessor(
                  this, new ChineseTextRecognizerOptions.Builder().build()));
          break;
        case TEXT_RECOGNITION_DEVANAGARI:
          cameraSource.setMachineLearningFrameProcessor(
              new TextRecognitionProcessor(
                  this, new DevanagariTextRecognizerOptions.Builder().build()));
          break;
        case TEXT_RECOGNITION_JAPANESE:
          cameraSource.setMachineLearningFrameProcessor(
              new TextRecognitionProcessor(
                  this, new JapaneseTextRecognizerOptions.Builder().build()));
          break;
        case TEXT_RECOGNITION_KOREAN:
          cameraSource.setMachineLearningFrameProcessor(
              new TextRecognitionProcessor(
                  this, new KoreanTextRecognizerOptions.Builder().build()));
          break;
        default:
          Log.e(TAG, "Unknown model: " + model);
      }

    } catch (RuntimeException e) {
      Toast.makeText(
              getApplicationContext(),
              "Can not create image processor: " + e.getMessage(),
              Toast.LENGTH_LONG)
          .show();
    }
  }

  /**
   * Starts or restarts the camera source, if it exists. If the camera source doesn't exist yet
   * (e.g., because onResume was called before the camera source was created), this will be called
   * again when the camera source is created.
   */
  private void startCameraSource() {
    if (cameraSource != null) {
      try {
        preview.start(cameraSource, graphicOverlay);
      } catch (IOException e) {
        cameraSource.release();
        cameraSource = null;
      }
    }
  }

  @Override
  public void onResume() {
    super.onResume();
    Log.d(TAG, "onResume");
    createCameraSource(selectedModel);
    startCameraSource();
  }

  /** Stops the camera. */
  @Override
  protected void onPause() {
    super.onPause();
    preview.stop();
  }

  @Override
  public void onDestroy() {
    super.onDestroy();
    if (cameraSource != null) {
      cameraSource.release();
    }
  }
}
