package com.example.lab6_2;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    TextView tvOut;
    Button btnOk;
    Button btnCancel;

    private static final String TAG = "myLogs";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Log.d(TAG, "Знайдемр View-елементи");
        tvOut = (TextView) findViewById(R.id.tvOut);
        btnOk = (Button) findViewById(R.id.btnOk);
        btnCancel = (Button) findViewById(R.id.btnCancel);

        Log.d(TAG, " привласнюємо обробник кнопкам");
        btnOk.setOnClickListener(this);
        btnCancel.setOnClickListener(this);

    }

    @Override
    public void onClick(View v) {
        Log.d(TAG, "по id визначаємо кнопку, що викликала цей оброблювач ");
        int elemId = v.getId();
        if (elemId == R.id.btnOk){
            Log.d(TAG, "кнопка ОК");
            tvOut.setText("Нажата кнопка ОК");
            Toast.makeText(this, "Натиснута кнопка ОК", Toast.LENGTH_LONG).show();
        }
        else if (elemId == R.id.btnCancel) {
            Log.d(TAG, "кнопка Cancel");
            tvOut.setText("Нажата кнопка Cancel");
            Toast.makeText(this, "Натиснута кнопка Cancel", Toast.LENGTH_LONG).show();
        }
    }

}