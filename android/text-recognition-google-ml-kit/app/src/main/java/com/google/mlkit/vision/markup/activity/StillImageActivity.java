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

import static java.lang.Math.max;

import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.ContentValues;
import android.content.Context;
import android.content.Intent;
import android.content.res.Configuration;
import android.graphics.Bitmap;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;

import androidx.appcompat.app.AppCompatActivity;
import android.util.Log;
import android.util.Pair;
import android.view.MenuInflater;
import android.view.View;
import android.view.ViewTreeObserver.OnGlobalLayoutListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ArrayAdapter;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.PopupMenu;
import android.widget.Spinner;
import android.widget.Toast;
import com.google.android.gms.common.annotation.KeepName;
import com.google.mlkit.vision.markup.GraphicOverlay;
import com.google.mlkit.vision.markup.R;
import com.google.mlkit.vision.markup.TextRecognitionProcessor;
import com.google.mlkit.vision.markup.VisionImageProcessor;
import com.google.mlkit.vision.markup.util.BitmapUtils;
import com.google.mlkit.vision.markup.util.PreferenceUtils;
import com.google.mlkit.vision.text.chinese.ChineseTextRecognizerOptions;
import com.google.mlkit.vision.text.devanagari.DevanagariTextRecognizerOptions;
import com.google.mlkit.vision.text.japanese.JapaneseTextRecognizerOptions;
import com.google.mlkit.vision.text.korean.KoreanTextRecognizerOptions;
import com.google.mlkit.vision.text.latin.TextRecognizerOptions;

import org.sdase.submission.documentscanner.DocumentScannerActivity;
import org.sdase.submission.documentscanner.constants.DocumentScannerExtra;
import org.sdase.submission.documentscanner.utils.FileUtil;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/** Activity demonstrating different image detector features with a still image from camera. */
@KeepName
public final class StillImageActivity extends AppCompatActivity {

  private static final String TAG = "StillImageActivity";

  private static final String OBJECT_DETECTION = "Object Detection";
  private static final String TEXT_RECOGNITION_LATIN = "Text Recognition Latin";
  private static final String TEXT_RECOGNITION_CHINESE = "Text Recognition Chinese";
  private static final String TEXT_RECOGNITION_DEVANAGARI = "Text Recognition Devanagari";
  private static final String TEXT_RECOGNITION_JAPANESE = "Text Recognition Japanese";
  private static final String TEXT_RECOGNITION_KOREAN = "Text Recognition Korean";
  private static final String SIZE_SCREEN = "w:screen"; // Match screen width
  private static final String SIZE_1024_768 = "w:1024"; // ~1024*768 in a normal ratio
  private static final String SIZE_640_480 = "w:640"; // ~640*480 in a normal ratio
  private static final String SIZE_ORIGINAL = "w:original"; // Original image size

  private static final String KEY_IMAGE_URI = "com.google.mlkit.vision.markup.KEY_IMAGE_URI";
  private static final String KEY_SELECTED_SIZE = "com.google.mlkit.vision.markup.KEY_SELECTED_SIZE";

  private static final int REQUEST_IMAGE_CAPTURE = 1001;
  private static final int REQUEST_CHOOSE_IMAGE = 1002;
  private static final int REQUEST_CROP_IMAGE = 1003;

  private FrameLayout refreshRecognitionButtonWrapper;
  private FrameLayout copyRecognitionButtonWrapper;
  private FrameLayout cropImageButtonWrapper;
  private ImageView preview;
  private GraphicOverlay graphicOverlay;
  private String selectedMode = OBJECT_DETECTION;
  private String selectedSize = SIZE_SCREEN;

  boolean isLandScape;

  private Uri imageUri;
  private Uri lastCroppedImageUri;
  private int imageMaxWidth;
  private int imageMaxHeight;

  private VisionImageProcessor imageProcessor;
  private StringBuilder processorAccumulator;


  private FileUtil fileUtil;

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);

    setContentView(R.layout.activity_still_image);

    if (savedInstanceState != null) {
      imageUri = savedInstanceState.getParcelable(KEY_IMAGE_URI);
      selectedSize = savedInstanceState.getString(KEY_SELECTED_SIZE);
    }

    fileUtil = new FileUtil(this);
    processorAccumulator = new StringBuilder();

    refreshRecognitionButtonWrapper = findViewById(R.id.refresh_recognition_button_wrapper);
    copyRecognitionButtonWrapper = findViewById(R.id.copy_recognition_button_wrapper);
    cropImageButtonWrapper = findViewById(R.id.crop_image_button_wrapper);

    findViewById(R.id.select_image_button)
        .setOnClickListener(
            view -> {
              // Menu for selecting either: a) take new photo b) select from existing
              PopupMenu popup = new PopupMenu(StillImageActivity.this, view);
              popup.setOnMenuItemClickListener(menuItem -> {
                int itemId = menuItem.getItemId();
                if (itemId == R.id.select_images_from_local) {
                  startChooseImageIntentForResult();
                  return true;
                } else if (itemId == R.id.take_photo_using_camera) {
                  startCameraIntentForResult();
                  return true;
                }
                return false;
              });
              MenuInflater inflater = popup.getMenuInflater();
              inflater.inflate(R.menu.camera_button_menu, popup.getMenu());
              popup.show();
            });

    findViewById(R.id.refresh_recognition_button)
            .setOnClickListener(
                    view -> {
                      tryReloadAndDetectInImage();
                    });

    findViewById(R.id.copy_recognition_button)
            .setOnClickListener(
                    view -> {
                      if (imageUri != null) {
                        if (processorAccumulator.length() == 0) {
                          Toast.makeText(this, "No text found", Toast.LENGTH_LONG).show();
                          return;
                        }
                        ClipboardManager clipboard = (ClipboardManager) getSystemService(Context.CLIPBOARD_SERVICE);
                        ClipData clip = ClipData.newPlainText("Scene text recognition result", processorAccumulator.toString());
                        clipboard.setPrimaryClip(clip);
                        Toast.makeText(this, "Recognition copied to clipboard", Toast.LENGTH_LONG).show();
                      }
                    });

    preview = findViewById(R.id.preview);

    graphicOverlay = findViewById(R.id.graphic_overlay);

    populateFeatureSelector();
    populateSizeSelector();

    isLandScape =
        (getResources().getConfiguration().orientation == Configuration.ORIENTATION_LANDSCAPE);

    View rootView = findViewById(R.id.root);
    rootView
        .getViewTreeObserver()
        .addOnGlobalLayoutListener(
            new OnGlobalLayoutListener() {
              @Override
              public void onGlobalLayout() {
                rootView.getViewTreeObserver().removeOnGlobalLayoutListener(this);
                imageMaxWidth = rootView.getWidth();
                imageMaxHeight = rootView.getHeight() - findViewById(R.id.control).getHeight();
                if (SIZE_SCREEN.equals(selectedSize)) {
                  tryReloadAndDetectInImage();
                }
              }
            });

    findViewById(R.id.settings_button).setOnClickListener(
        v -> {
          Intent intent = new Intent(getApplicationContext(), SettingsActivity.class);
          intent.putExtra(
              SettingsActivity.EXTRA_LAUNCH_SOURCE, SettingsActivity.LaunchSource.STILL_IMAGE);
          startActivity(intent);
        });

    findViewById(R.id.crop_image_button).setOnClickListener(
            v -> {
              if (imageUri == null){
                Toast.makeText(this, "Image not selected", Toast.LENGTH_LONG).show();
                return;
              }
              Intent intent = new Intent(this, DocumentScannerActivity.class);
              intent.putExtra(DocumentScannerExtra.EXTRA_LET_USER_ADJUST_CROP, PreferenceUtils.letUserAdjustCrop(this));
              intent.putExtra(MediaStore.EXTRA_OUTPUT, imageUri.toString());
              startActivityForResult(intent, REQUEST_CROP_IMAGE);
            });
  }

  @Override
  public void onResume() {
    super.onResume();
    createImageProcessor();
    tryReloadAndDetectInImage();
  }

  @Override
  public void onPause() {
    super.onPause();
    if (imageProcessor != null) {
      imageProcessor.stop();
    }
  }

  private void tryDeleteLastCropFile() {
    if (lastCroppedImageUri != null) {
      String pathToDelete = fileUtil.getPath(lastCroppedImageUri);
      if (pathToDelete != null) {
        new File(pathToDelete).delete();
      }
    }
  }

  @Override
  public void onDestroy() {
    super.onDestroy();
    if (imageProcessor != null) {
      imageProcessor.stop();
    }
    tryDeleteLastCropFile();
  }

  private void populateFeatureSelector() {
    Spinner featureSpinner = findViewById(R.id.feature_selector);
    List<String> options = new ArrayList<>();
    options.add(TEXT_RECOGNITION_LATIN);
    options.add(TEXT_RECOGNITION_CHINESE);
    options.add(TEXT_RECOGNITION_DEVANAGARI);
    options.add(TEXT_RECOGNITION_JAPANESE);
    options.add(TEXT_RECOGNITION_KOREAN);

    // Creating adapter for featureSpinner
    ArrayAdapter<String> dataAdapter = new ArrayAdapter<>(this, R.layout.spinner_style, options);
    // Drop down layout style - list view with radio button
    dataAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
    // attaching data adapter to spinner
    featureSpinner.setAdapter(dataAdapter);
    featureSpinner.setOnItemSelectedListener(
        new OnItemSelectedListener() {
          @Override
          public void onItemSelected(
              AdapterView<?> parentView, View selectedItemView, int pos, long id) {
            selectedMode = parentView.getItemAtPosition(pos).toString();
            createImageProcessor();
            tryReloadAndDetectInImage();
          }
          @Override
          public void onNothingSelected(AdapterView<?> arg0) {}
        });
  }

  private void populateSizeSelector() {
    Spinner sizeSpinner = findViewById(R.id.size_selector);
    List<String> options = new ArrayList<>();
    options.add(SIZE_SCREEN);
    options.add(SIZE_1024_768);
    options.add(SIZE_640_480);
    options.add(SIZE_ORIGINAL);

    // Creating adapter for featureSpinner
    ArrayAdapter<String> dataAdapter = new ArrayAdapter<>(this, R.layout.spinner_style, options);
    // Drop down layout style - list view with radio button
    dataAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
    // attaching data adapter to spinner
    sizeSpinner.setAdapter(dataAdapter);
    sizeSpinner.setOnItemSelectedListener(
        new OnItemSelectedListener() {

          @Override
          public void onItemSelected(
              AdapterView<?> parentView, View selectedItemView, int pos, long id) {
            selectedSize = parentView.getItemAtPosition(pos).toString();
            tryReloadAndDetectInImage();
          }

          @Override
          public void onNothingSelected(AdapterView<?> arg0) {}
        });
  }

  @Override
  public void onSaveInstanceState(Bundle outState) {
    super.onSaveInstanceState(outState);
    outState.putParcelable(KEY_IMAGE_URI, imageUri);
    outState.putString(KEY_SELECTED_SIZE, selectedSize);
  }

  private void startCameraIntentForResult() {
    // Clean up last time's image
    imageUri = null;
    preview.setImageBitmap(null);

    Intent takePictureIntent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
    if (takePictureIntent.resolveActivity(getPackageManager()) != null) {
      ContentValues values = new ContentValues();
      values.put(MediaStore.Images.Media.TITLE, "New Picture");
      values.put(MediaStore.Images.Media.DESCRIPTION, "From Camera");
      imageUri = getContentResolver().insert(MediaStore.Images.Media.EXTERNAL_CONTENT_URI, values);
      takePictureIntent.putExtra(MediaStore.EXTRA_OUTPUT, imageUri);
      startActivityForResult(takePictureIntent, REQUEST_IMAGE_CAPTURE);
    }
  }

  private void startChooseImageIntentForResult() {
    Intent intent = new Intent();
    intent.setType("image/*");
    intent.setAction(Intent.ACTION_GET_CONTENT);
    startActivityForResult(Intent.createChooser(intent, "Select Picture"), REQUEST_CHOOSE_IMAGE);
  }

  @Override
  protected void onActivityResult(int requestCode, int resultCode, Intent data) {
    if (requestCode == REQUEST_IMAGE_CAPTURE && resultCode == RESULT_OK) {
      tryReloadAndDetectInImage();
    } else if (requestCode == REQUEST_CHOOSE_IMAGE && resultCode == RESULT_OK) {
      // In this case, imageUri is returned by the chooser, save it.
      imageUri = data.getData();
      tryReloadAndDetectInImage();
    } else if (requestCode == REQUEST_CROP_IMAGE) {
      if (resultCode == RESULT_OK){
        Uri resultCropUri;
        try {
          resultCropUri = data.getData();
          if (resultCropUri == null) {
            throw new Exception("CropUri not recieced");
          }
          tryDeleteLastCropFile();
          lastCroppedImageUri = resultCropUri;
          imageUri = resultCropUri;
          tryReloadAndDetectInImage();
        } catch (Exception e) {
          Log.e(TAG, "Can not recieve CropUri: ", e);
          Toast.makeText(
                  getApplicationContext(),
                  "Can not recieve CropUri: " + e.getMessage(),
                  Toast.LENGTH_LONG)
                  .show();
        }
      } else {
        super.onActivityResult(requestCode, resultCode, data);
      }
    } else {
      super.onActivityResult(requestCode, resultCode, data);
    }
  }

  private void tryReloadAndDetectInImage() {
    try {
      if (imageUri == null) {
        return;
      }

      if (SIZE_SCREEN.equals(selectedSize) && imageMaxWidth == 0) {
        // UI layout has not finished yet, will reload once it's ready.
        return;
      }

      Bitmap imageBitmap = BitmapUtils.getBitmapFromContentUri(getContentResolver(), imageUri);
      if (imageBitmap == null) {
        return;
      }

      // Clear the overlay first
      graphicOverlay.clear();

      Bitmap resizedBitmap;
      if (selectedSize.equals(SIZE_ORIGINAL)) {
        resizedBitmap = imageBitmap;
      } else {
        // Get the dimensions of the image view
        Pair<Integer, Integer> targetedSize = getTargetedWidthHeight();

        // Determine how much to scale down the image
        float scaleFactor =
            max(
                (float) imageBitmap.getWidth() / (float) targetedSize.first,
                (float) imageBitmap.getHeight() / (float) targetedSize.second);

        resizedBitmap =
            Bitmap.createScaledBitmap(
                imageBitmap,
                (int) (imageBitmap.getWidth() / scaleFactor),
                (int) (imageBitmap.getHeight() / scaleFactor),
                true);
      }

      preview.setImageBitmap(resizedBitmap);

      if (imageProcessor != null) {
        processorAccumulator.setLength(0);
        graphicOverlay.setImageSourceInfo(
            resizedBitmap.getWidth(), resizedBitmap.getHeight(), /* isFlipped= */ false);
        imageProcessor.processBitmap(resizedBitmap, graphicOverlay);
        if (imageUri != null) {
          refreshRecognitionButtonWrapper.setVisibility(View.VISIBLE);
          copyRecognitionButtonWrapper.setVisibility(View.VISIBLE);
          cropImageButtonWrapper.setVisibility(View.VISIBLE);
        }
      } else {
        Log.e(TAG, "Null imageProcessor, please check adb logs for imageProcessor creation error");
      }
    } catch (IOException e) {
      Log.e(TAG, "Error retrieving saved image");
      imageUri = null;
    }
  }

  private Pair<Integer, Integer> getTargetedWidthHeight() {
    int targetWidth;
    int targetHeight;

    switch (selectedSize) {
      case SIZE_SCREEN:
        targetWidth = imageMaxWidth;
        targetHeight = imageMaxHeight;
        break;
      case SIZE_640_480:
        targetWidth = isLandScape ? 640 : 480;
        targetHeight = isLandScape ? 480 : 640;
        break;
      case SIZE_1024_768:
        targetWidth = isLandScape ? 1024 : 768;
        targetHeight = isLandScape ? 768 : 1024;
        break;
      default:
        throw new IllegalStateException("Unknown size");
    }

    return new Pair<>(targetWidth, targetHeight);
  }

  private void createImageProcessor() {
    if (imageProcessor != null) {
      imageProcessor.stop();
    }
    try {
      switch (selectedMode) {
        case TEXT_RECOGNITION_LATIN:
          imageProcessor =
              new TextRecognitionProcessor(
                  this, new TextRecognizerOptions.Builder().build(), processorAccumulator);
          break;
        case TEXT_RECOGNITION_CHINESE:
          imageProcessor =
              new TextRecognitionProcessor(
                  this, new ChineseTextRecognizerOptions.Builder().build(), processorAccumulator);
          break;
        case TEXT_RECOGNITION_DEVANAGARI:
          imageProcessor =
              new TextRecognitionProcessor(
                  this, new DevanagariTextRecognizerOptions.Builder().build(), processorAccumulator);
          break;
        case TEXT_RECOGNITION_JAPANESE:
          imageProcessor =
              new TextRecognitionProcessor(
                  this, new JapaneseTextRecognizerOptions.Builder().build(), processorAccumulator);
          break;
        case TEXT_RECOGNITION_KOREAN:
          imageProcessor =
              new TextRecognitionProcessor(
                  this, new KoreanTextRecognizerOptions.Builder().build(), processorAccumulator);
          break;
        default:
          Log.e(TAG, "Unknown selectedMode: " + selectedMode);
      }
    } catch (Exception e) {
      Log.e(TAG, "Can not create image processor: " + selectedMode, e);
      Toast.makeText(
              getApplicationContext(),
              "Can not create image processor: " + e.getMessage(),
              Toast.LENGTH_LONG)
          .show();
    }
  }
}
