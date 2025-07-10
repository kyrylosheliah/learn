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

import android.os.Bundle;
import android.preference.PreferenceFragment;
import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;
import com.google.mlkit.vision.markup.R;

import android.hardware.Camera;
import android.preference.ListPreference;
import android.preference.PreferenceCategory;

import androidx.annotation.StringRes;
import com.google.mlkit.vision.markup.CameraSource;
import com.google.mlkit.vision.markup.CameraSource.SizePair;
import com.google.mlkit.vision.markup.util.PreferenceUtils;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Hosts the preference fragment to configure settings for a demo activity that specified by the
 * {@link LaunchSource}.
 */
public class SettingsActivity extends AppCompatActivity {


  /** Configures live preview demo settings. */
  public static class LivePreviewPreferenceFragment extends PreferenceFragment {

    @Override
    public void onCreate(Bundle savedInstanceState) {
      super.onCreate(savedInstanceState);

      addPreferencesFromResource(R.xml.preference_live_preview_quickstart);
      setUpCameraPreferences();
    }

    void setUpCameraPreferences() {
      PreferenceCategory cameraPreference =
              (PreferenceCategory) findPreference(getString(R.string.pref_category_key_camera));
      cameraPreference.removePreference(
              findPreference(getString(R.string.pref_key_camerax_rear_camera_target_resolution)));
      cameraPreference.removePreference(
              findPreference(getString(R.string.pref_key_camerax_front_camera_target_resolution)));
      setUpCameraPreviewSizePreference(
              R.string.pref_key_rear_camera_preview_size,
              R.string.pref_key_rear_camera_picture_size,
              CameraSource.CAMERA_FACING_BACK);
      setUpCameraPreviewSizePreference(
              R.string.pref_key_front_camera_preview_size,
              R.string.pref_key_front_camera_picture_size,
              CameraSource.CAMERA_FACING_FRONT);
    }

    private void setUpCameraPreviewSizePreference(
            @StringRes int previewSizePrefKeyId, @StringRes int pictureSizePrefKeyId, int cameraId) {
      ListPreference previewSizePreference =
              (ListPreference) findPreference(getString(previewSizePrefKeyId));

      Camera camera = null;
      try {
        camera = Camera.open(cameraId);

        List<SizePair> previewSizeList = CameraSource.generateValidPreviewSizeList(camera);
        String[] previewSizeStringValues = new String[previewSizeList.size()];
        Map<String, String> previewToPictureSizeStringMap = new HashMap<>();
        for (int i = 0; i < previewSizeList.size(); i++) {
          SizePair sizePair = previewSizeList.get(i);
          previewSizeStringValues[i] = sizePair.preview.toString();
          if (sizePair.picture != null) {
            previewToPictureSizeStringMap.put(
                    sizePair.preview.toString(), sizePair.picture.toString());
          }
        }
        previewSizePreference.setEntries(previewSizeStringValues);
        previewSizePreference.setEntryValues(previewSizeStringValues);

        if (previewSizePreference.getEntry() == null) {
          // First time of opening the Settings page.
          SizePair sizePair =
                  CameraSource.selectSizePair(
                          camera,
                          CameraSource.DEFAULT_REQUESTED_CAMERA_PREVIEW_WIDTH,
                          CameraSource.DEFAULT_REQUESTED_CAMERA_PREVIEW_HEIGHT);
          String previewSizeString = sizePair.preview.toString();
          previewSizePreference.setValue(previewSizeString);
          previewSizePreference.setSummary(previewSizeString);
          PreferenceUtils.saveString(
                  getActivity(),
                  pictureSizePrefKeyId,
                  sizePair.picture != null ? sizePair.picture.toString() : null);
        } else {
          previewSizePreference.setSummary(previewSizePreference.getEntry());
        }

        previewSizePreference.setOnPreferenceChangeListener(
                (preference, newValue) -> {
                  String newPreviewSizeStringValue = (String) newValue;
                  previewSizePreference.setSummary(newPreviewSizeStringValue);
                  PreferenceUtils.saveString(
                          getActivity(),
                          pictureSizePrefKeyId,
                          previewToPictureSizeStringMap.get(newPreviewSizeStringValue));
                  return true;
                });
      } catch (RuntimeException e) {
        // If there's no camera for the given camera id, hide the corresponding preference.
        ((PreferenceCategory) findPreference(getString(R.string.pref_category_key_camera)))
                .removePreference(previewSizePreference);
      } finally {
        if (camera != null) {
          camera.release();
        }
      }
    }
  }

  /** Configures still image demo settings. */
  public static class StillImagePreferenceFragment extends PreferenceFragment {
    @Override
    public void onCreate(Bundle savedInstanceState) {
      super.onCreate(savedInstanceState);
      addPreferencesFromResource(R.xml.preference_still_image);
    }
  }
  public static final String EXTRA_LAUNCH_SOURCE = "extra_launch_source";

  /** Specifies where this activity is launched from. */
  @SuppressWarnings("NewApi") // CameraX is only available on API 21+
  public enum LaunchSource {
    LIVE_PREVIEW(R.string.pref_screen_title_live_preview, LivePreviewPreferenceFragment.class),
    STILL_IMAGE(R.string.pref_screen_title_still_image, StillImagePreferenceFragment.class);

    private final int titleResId;
    private final Class<? extends PreferenceFragment> prefFragmentClass;

    LaunchSource(int titleResId, Class<? extends PreferenceFragment> prefFragmentClass) {
      this.titleResId = titleResId;
      this.prefFragmentClass = prefFragmentClass;
    }
  }

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);

    setContentView(R.layout.activity_settings);

    LaunchSource launchSource =
        (LaunchSource) getIntent().getSerializableExtra(EXTRA_LAUNCH_SOURCE);
    ActionBar actionBar = getSupportActionBar();
    if (actionBar != null) {
      actionBar.setTitle(launchSource.titleResId);
    }

    try {
      getFragmentManager()
          .beginTransaction()
          .replace(
              R.id.settings_container,
              launchSource.prefFragmentClass.getDeclaredConstructor().newInstance())
          .commit();
    } catch (Exception e) {
      throw new RuntimeException(e);
    }
  }
}
