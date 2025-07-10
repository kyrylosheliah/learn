package com.example.srs1;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.MotionEvent;
import android.widget.RelativeLayout;

/** * Created by Kalidoss on 18/07/16. */


public class MainActivity extends AppCompatActivity {

    public GLSurfaceView mGLSurfaceView;
    float mPreviousX,mPreviousY;
    private final float TOUCH_SCALE_FACTOR = 180.0f / 320;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView( R.layout.activity_main);
        graphicView = new GraphicView(this);
    }

    private  GraphicView graphicView;

    @Override
    protected void onResume() {
        super.onResume();
        if (graphicView != null) {
            graphicView.onResume();
        }
    }

    @Override
    protected void onDestroy() {
        graphicView.onPause();
        super.onDestroy();
    }
}