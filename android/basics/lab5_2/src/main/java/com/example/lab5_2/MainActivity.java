package com.example.lab5_2;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    TextView tvOut;
    Button btnOk;
    Button btnCancel;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        tvOut = (TextView) findViewById(R.id.tvOut);
        btnOk = (Button) findViewById(R.id.btnOk);
        btnCancel = (Button) findViewById(R.id.btnCancel);

        View.OnClickListener oclBtn = new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                int elemId = v.getId();
                if (elemId == R.id.btnOk){
                    tvOut.setText("Нажата кнопка ОК");
                }
                else if (elemId == R.id.btnCancel)
                {
                    tvOut.setText("Нажата кнопка Cancel");
                }
            }
        };

        // btnOk.setOnClickListener(oclBtn);
        // btnCancel.setOnClickListener(oclBtn);

        btnOk.setOnClickListener(this);
        btnCancel.setOnClickListener(this);
    }

    public void onClick(View v)
    {
        int elemId = v.getId();
        if (elemId == R.id.btnOk){
            tvOut.setText("Нажата кнопка ОК");
        }
        else if (elemId == R.id.btnCancel)
        {
            tvOut.setText("Нажата кнопка Cancel");
        }
    }

}