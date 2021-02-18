package com.jtl.learnopengles;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

/**
 * @author TianLong
 * @date 2021/2/6 11:10
 */
public class MainActivity extends AppCompatActivity {
    static {
        System.loadLibrary("opengles_util");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        TextView tv = findViewById(R.id.sample_text);
        tv.setText("");
    }
}