package com.jtl.learnopengles;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;

import com.jtl.learnopengles.glview.OpenGLSurface;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

/**
 * @author TianLong
 * @date 2021/2/6 11:10
 */
public class MainActivity extends AppCompatActivity {
    private OpenGLSurface mOpenGLSurface;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mOpenGLSurface = findViewById(R.id.open_gl_surface);

        Bitmap bitmap = BitmapFactory.decodeResource(this.getResources(),R.mipmap.hello_lihuanying);
        int wi = bitmap.getWidth();
        int hi = bitmap.getHeight();

        ByteBuffer data = ByteBuffer.allocateDirect(wi*hi*4).order(ByteOrder.nativeOrder());

        bitmap.copyPixelsToBuffer(data);
        data.position(0);
        mOpenGLSurface.setDataBuffer(wi,hi,data);
    }
}