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

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.view.View;
import com.google.common.base.Preconditions;
import com.google.common.primitives.Ints;
import java.util.ArrayList;
import java.util.List;

import static java.lang.Math.max;
import static java.lang.Math.min;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.RectF;
import android.util.Log;
import com.google.mlkit.vision.markup.GraphicOverlay;
import com.google.mlkit.vision.markup.GraphicOverlay.Graphic;
import com.google.mlkit.vision.text.Text;
import com.google.mlkit.vision.text.Text.Element;
import com.google.mlkit.vision.text.Text.Line;
import com.google.mlkit.vision.text.Text.Symbol;
import com.google.mlkit.vision.text.Text.TextBlock;
import java.util.Arrays;
import java.util.Locale;


/**
 * A view which renders a series of custom graphics to be overlayed on top of an associated preview
 * (i.e., the camera preview). The creator can add graphics objects, update the objects, and remove
 * them, triggering the appropriate drawing and invalidation within the view.
 *
 * <p>Supports scaling and mirroring of the graphics relative the camera's preview properties. The
 * idea is that detection items are expressed in terms of an image size, but need to be scaled up to
 * the full view size, and also mirrored in the case of the front-facing camera.
 *
 * <p>Associated {@link Graphic} items should use the following methods to convert to view
 * coordinates for the graphics that are drawn:
 *
 * <ol>
 *   <li>{@link Graphic#scale(float)} adjusts the size of the supplied value from the image scale to
 *       the view scale.
 *   <li>{@link Graphic#translateX(float)} and {@link Graphic#translateY(float)} adjust the
 *       coordinate from the image's coordinate system to the view coordinate system.
 * </ol>
 */
public class GraphicOverlay extends View {
  private final Object lock = new Object();
  private final List<Graphic> graphics = new ArrayList<>();
  // Matrix for transforming from image coordinates to overlay view coordinates.
  private final Matrix transformationMatrix = new Matrix();

  private int imageWidth;
  private int imageHeight;
  // The factor of overlay View size to image size. Anything in the image coordinates need to be
  // scaled by this amount to fit with the area of overlay View.
  private float scaleFactor = 1.0f;
  // The number of horizontal pixels needed to be cropped on each side to fit the image with the
  // area of overlay View after scaling.
  private float postScaleWidthOffset;
  // The number of vertical pixels needed to be cropped on each side to fit the image with the
  // area of overlay View after scaling.
  private float postScaleHeightOffset;
  private boolean isImageFlipped;
  private boolean needUpdateTransformation = true;

  /**
   * Base class for a custom graphics object to be rendered within the graphic overlay. Subclass
   * this and implement the {@link Graphic#draw(Canvas)} method to define the graphics element. Add
   * instances to the overlay using {@link GraphicOverlay#add(Graphic)}.
   */
  public abstract static class Graphic {
    private GraphicOverlay overlay;

    public Graphic(GraphicOverlay overlay) {
      this.overlay = overlay;
    }

    /**
     * Draw the graphic on the supplied canvas. Drawing should use the following methods to convert
     * to view coordinates for the graphics that are drawn:
     *
     * <ol>
     *   <li>{@link Graphic#scale(float)} adjusts the size of the supplied value from the image
     *       scale to the view scale.
     *   <li>{@link Graphic#translateX(float)} and {@link Graphic#translateY(float)} adjust the
     *       coordinate from the image's coordinate system to the view coordinate system.
     * </ol>
     *
     * @param canvas drawing canvas
     */
    public abstract void draw(Canvas canvas);

    /** Adjusts the supplied value from the image scale to the view scale. */
    public float scale(float imagePixel) {
      return imagePixel * overlay.scaleFactor;
    }

    /**
     * Adjusts the x coordinate from the image's coordinate system to the view coordinate system.
     */
    public float translateX(float x) {
      if (overlay.isImageFlipped) {
        return overlay.getWidth() - (scale(x) - overlay.postScaleWidthOffset);
      } else {
        return scale(x) - overlay.postScaleWidthOffset;
      }
    }

    /**
     * Adjusts the y coordinate from the image's coordinate system to the view coordinate system.
     */
    public float translateY(float y) {
      return scale(y) - overlay.postScaleHeightOffset;
    }

    /**
     * Returns a {@link Matrix} for transforming from image coordinates to overlay view coordinates.
     */
    public Matrix getTransformationMatrix() {
      return overlay.transformationMatrix;
    }

    public void postInvalidate() {
      overlay.postInvalidate();
    }

  }

  public GraphicOverlay(Context context, AttributeSet attrs) {
    super(context, attrs);
    addOnLayoutChangeListener(
        (view, left, top, right, bottom, oldLeft, oldTop, oldRight, oldBottom) ->
            needUpdateTransformation = true);
  }

  /** Removes all graphics from the overlay. */
  public void clear() {
    synchronized (lock) {
      graphics.clear();
    }
    postInvalidate();
  }

  /** Adds a graphic to the overlay. */
  public void add(Graphic graphic) {
    synchronized (lock) {
      graphics.add(graphic);
    }
  }

  /**
   * Sets the source information of the image being processed by detectors, including size and
   * whether it is flipped, which informs how to transform image coordinates later.
   *
   * @param imageWidth the width of the image sent to ML Kit detectors
   * @param imageHeight the height of the image sent to ML Kit detectors
   * @param isFlipped whether the image is flipped. Should set it to true when the image is from the
   *     front camera.
   */
  public void setImageSourceInfo(int imageWidth, int imageHeight, boolean isFlipped) {
    Preconditions.checkState(imageWidth > 0, "image width must be positive");
    Preconditions.checkState(imageHeight > 0, "image height must be positive");
    synchronized (lock) {
      this.imageWidth = imageWidth;
      this.imageHeight = imageHeight;
      this.isImageFlipped = isFlipped;
      needUpdateTransformation = true;
    }
    postInvalidate();
  }

  private void updateTransformationIfNeeded() {
    if (!needUpdateTransformation || imageWidth <= 0 || imageHeight <= 0) {
      return;
    }
    float viewAspectRatio = (float) getWidth() / getHeight();
    float imageAspectRatio = (float) imageWidth / imageHeight;
    postScaleWidthOffset = 0;
    postScaleHeightOffset = 0;
    if (viewAspectRatio > imageAspectRatio) {
      // The image needs to be vertically cropped to be displayed in this view.
      scaleFactor = (float) getWidth() / imageWidth;
      postScaleHeightOffset = ((float) getWidth() / imageAspectRatio - getHeight()) / 2;
    } else {
      // The image needs to be horizontally cropped to be displayed in this view.
      scaleFactor = (float) getHeight() / imageHeight;
      postScaleWidthOffset = ((float) getHeight() * imageAspectRatio - getWidth()) / 2;
    }

    transformationMatrix.reset();
    transformationMatrix.setScale(scaleFactor, scaleFactor);
    transformationMatrix.postTranslate(-postScaleWidthOffset, -postScaleHeightOffset);

    if (isImageFlipped) {
      transformationMatrix.postScale(-1f, 1f, getWidth() / 2f, getHeight() / 2f);
    }

    needUpdateTransformation = false;
  }

  /** Draws the overlay with its associated graphic objects. */
  @Override
  protected void onDraw(Canvas canvas) {
    super.onDraw(canvas);

    synchronized (lock) {
      updateTransformationIfNeeded();

      for (Graphic graphic : graphics) {
        graphic.draw(canvas);
      }
    }
  }


  /**
   * Graphic instance for rendering TextBlock position, size, and ID within an associated graphic
   * overlay view.
   */
  public static class TextGraphic extends Graphic {

    private static final String TAG = "TextGraphic";
    private static final String TEXT_WITH_LANGUAGE_TAG_FORMAT = "%s:%s";

    private static final int TEXT_COLOR = Color.BLACK;
    private static final int MARKER_COLOR = Color.WHITE;
    private static final float TEXT_SIZE = 54.0f;
    private static final float STROKE_WIDTH = 4.0f;

    private final Paint rectPaint;
    private final Paint textPaint;
    private final Paint labelPaint;
    private final Text text;
    private final boolean shouldGroupTextInBlocks;
    private final boolean showLanguageTag;
    private final boolean showConfidence;

    TextGraphic(
            GraphicOverlay overlay,
            Text text,
            boolean shouldGroupTextInBlocks,
            boolean showLanguageTag,
            boolean showConfidence) {
      super(overlay);

      this.text = text;
      this.shouldGroupTextInBlocks = shouldGroupTextInBlocks;
      this.showLanguageTag = showLanguageTag;
      this.showConfidence = showConfidence;

      rectPaint = new Paint();
      rectPaint.setColor(MARKER_COLOR);
      rectPaint.setStyle(Paint.Style.STROKE);
      rectPaint.setStrokeWidth(STROKE_WIDTH);

      textPaint = new Paint();
      textPaint.setColor(TEXT_COLOR);
      textPaint.setTextSize(TEXT_SIZE);

      labelPaint = new Paint();
      labelPaint.setColor(MARKER_COLOR);
      labelPaint.setStyle(Paint.Style.FILL);
      // Redraw the overlay, as this graphic has been added.
      postInvalidate();
    }

    /** Draws the text block annotations for position, size, and raw value on the supplied canvas. */
    @Override
    public void draw(Canvas canvas) {
      /*Log.d(TAG, "Text is: " + text.getText());*/
      for (TextBlock textBlock : text.getTextBlocks()) {
        // Renders the text at the bottom of the box.
      /*Log.d(TAG, "TextBlock text is: " + textBlock.getText());
      Log.d(TAG, "TextBlock boundingbox is: " + textBlock.getBoundingBox());
      Log.d(TAG, "TextBlock cornerpoint is: " + Arrays.toString(textBlock.getCornerPoints()));*/
        if (shouldGroupTextInBlocks) {
          String text = showLanguageTag
                  ? String.format(TEXT_WITH_LANGUAGE_TAG_FORMAT, textBlock.getRecognizedLanguage(), textBlock.getText())
                  : textBlock.getText();
          drawText(
                  text,
                  new RectF(textBlock.getBoundingBox()),
                  TEXT_SIZE * textBlock.getLines().size() + 2 * STROKE_WIDTH,
                  canvas);
        } else {
          for (Line line : textBlock.getLines()) {
          /*Log.d(TAG, "Line text is: " + line.getText());
          Log.d(TAG, "Line boundingbox is: " + line.getBoundingBox());
          Log.d(TAG, "Line cornerpoint is: " + Arrays.toString(line.getCornerPoints()));
          Log.d(TAG, "Line confidence is: " + line.getConfidence());
          Log.d(TAG, "Line angle is: " + line.getAngle());*/
            String text = showLanguageTag
                    ? String.format(TEXT_WITH_LANGUAGE_TAG_FORMAT, line.getRecognizedLanguage(), line.getText())
                    : line.getText();
            text = showConfidence
                    ? String.format(Locale.US, "%s (%.2f)", text, line.getConfidence())
                    : text;
            drawText(text, new RectF(line.getBoundingBox()), TEXT_SIZE + 2 * STROKE_WIDTH, canvas);
          /*for (Element element : line.getElements()) {
            Log.d(TAG, "Element text is: " + element.getText());
            Log.d(TAG, "Element boundingbox is: " + element.getBoundingBox());
            Log.d(TAG, "Element cornerpoint is: " + Arrays.toString(element.getCornerPoints()));
            Log.d(TAG, "Element language is: " + element.getRecognizedLanguage());
            Log.d(TAG, "Element confidence is: " + element.getConfidence());
            Log.d(TAG, "Element angle is: " + element.getAngle());
            for (Symbol symbol : element.getSymbols()) {
              Log.d(TAG, "Symbol text is: " + symbol.getText());
              Log.d(TAG, "Symbol boundingbox is: " + symbol.getBoundingBox());
              Log.d(TAG, "Symbol cornerpoint is: " + Arrays.toString(symbol.getCornerPoints()));
              Log.d(TAG, "Symbol confidence is: " + symbol.getConfidence());
              Log.d(TAG, "Symbol angle is: " + symbol.getAngle());
            }
          }*/
          }
        }
      }
    }

    private void drawText(String text, RectF rect, float textHeight, Canvas canvas) {
      // If the image is flipped, the left will be translated to right, and the right to left.
      float x0 = translateX(rect.left);
      float x1 = translateX(rect.right);
      rect.left = min(x0, x1);
      rect.right = max(x0, x1);
      rect.top = translateY(rect.top);
      rect.bottom = translateY(rect.bottom);
      canvas.drawRect(rect, rectPaint);
      float textWidth = textPaint.measureText(text);
      canvas.drawRect(
              rect.left - STROKE_WIDTH,
              rect.top - textHeight,
              rect.left + textWidth + 2 * STROKE_WIDTH,
              rect.top,
              labelPaint);
      // Renders the text at the bottom of the box.
      canvas.drawText(text, rect.left, rect.top - STROKE_WIDTH, textPaint);
    }
  }

}
