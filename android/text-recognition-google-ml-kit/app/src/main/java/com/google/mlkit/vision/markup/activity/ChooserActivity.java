
package com.google.mlkit.vision.markup.activity;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

import android.Manifest;
import android.content.pm.PackageManager;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import com.google.mlkit.vision.markup.R;

import java.util.ArrayList;

public final class ChooserActivity extends AppCompatActivity
    implements ActivityCompat.OnRequestPermissionsResultCallback {

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    /*if (BuildConfig.DEBUG) {
      StrictMode.setThreadPolicy(new StrictMode.ThreadPolicy.Builder().detectAll().penaltyLog().build());
      StrictMode.setVmPolicy(new StrictMode.VmPolicy.Builder().detectLeakedSqlLiteObjects().detectLeakedClosableObjects().penaltyLog().build());
    }*/
    super.onCreate(savedInstanceState);
    if (!allRuntimePermissionsGranted()) {
      getRuntimePermissions();
    }
    setContentView(R.layout.activity_chooser);
    findViewById(R.id.textview_camera_source_activity).setOnClickListener(view -> startActivity(new Intent(ChooserActivity.this, LivePreviewActivity.class)));
    findViewById(R.id.textview_still_image_activity).setOnClickListener(view -> startActivity(new Intent(ChooserActivity.this, StillImageActivity.class)));
  }

  private static final int PERMISSION_REQUESTS = 1;
  private static final String[] REQUIRED_RUNTIME_PERMISSIONS = {
          Manifest.permission.CAMERA,
          Manifest.permission.WRITE_EXTERNAL_STORAGE,
          Manifest.permission.READ_EXTERNAL_STORAGE
  };


  private boolean allRuntimePermissionsGranted() {
    for (String permission : REQUIRED_RUNTIME_PERMISSIONS) {
      if (!isPermissionGranted(this, permission)) {
        return false;
      }
    }
    return true;
  }

  private void getRuntimePermissions() {
    ArrayList<String> permissionsToRequest = new ArrayList<>();
    for (String permission : REQUIRED_RUNTIME_PERMISSIONS) {
      if (!isPermissionGranted(this, permission)) {
        permissionsToRequest.add(permission);
      }
    }
    if (!permissionsToRequest.isEmpty()) {
      ActivityCompat.requestPermissions(
              this,
              permissionsToRequest.toArray(new String[0]),
              PERMISSION_REQUESTS
      );
    }
  }

  private boolean isPermissionGranted(Context context, String permission) {
    return ContextCompat.checkSelfPermission(context, permission) == PackageManager.PERMISSION_GRANTED;
  }

}
