package com.jtl.learnopengles;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLES20;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.Button;
import android.widget.ImageView;

import com.jtl.learnopengles.glview.OpenGLSurface;

import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

/**
 * @author TianLong
 * @date 2021/2/6 11:10
 */
public class MainActivity extends AppCompatActivity {
    private OpenGLSurface mOpenGLSurface;
    private ImageView mImageView;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mOpenGLSurface = findViewById(R.id.open_gl_surface);
        mImageView = findViewById(R.id.sample_image);
        Bitmap bitmap = BitmapFactory.decodeResource(this.getResources(),R.mipmap.taiquan1);
        int wi = bitmap.getWidth();
        int hi = bitmap.getHeight();

        ByteBuffer data = ByteBuffer.allocateDirect(wi*hi*4).order(ByteOrder.nativeOrder());

        bitmap.copyPixelsToBuffer(data);
        data.position(0);
        mOpenGLSurface.setDataBuffer(wi,hi,data);

        new Thread(new Runnable() {
            @Override
            public void run() {
                while (true){
                    try {
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    mOpenGLSurface.queueEvent(new Runnable() {
                        @Override
                        public void run() {
                            ByteBuffer B = ByteBuffer.allocateDirect(wi*hi*4).order(ByteOrder.nativeOrder());
                            long tt = System.currentTimeMillis();
                            GLES20.glReadPixels(0,0,wi,hi,GLES20.GL_RGBA,GLES20.GL_UNSIGNED_BYTE,B);
                            Log.w("TIME",(System.currentTimeMillis()-tt)+"ms");
                            Bitmap bitmap1 = Bitmap.createBitmap(wi,hi, Bitmap.Config.ARGB_8888);

                            bitmap1.copyPixelsFromBuffer(B);
                            mImageView.post(new Runnable() {
                                @Override
                                public void run() {
                                    mImageView.setImageBitmap(bitmap1);
                                }
                            });
                        }
                    });
                }
            }
        }).start();


//
//        try {
//            InputStream inputStream = this.getAssets().open("test_rgb.raw");
//            Log.w("CHANGDU",inputStream.available()/640/480+"");
//            byte[] rawData = new byte[inputStream.available()];
//            byte[] rawRGBAData = new byte[rawData.length/3*4];
//
//
//
//            ByteBuffer byteBuffer = ByteBuffer.allocateDirect(rawRGBAData.length).order(ByteOrder.nativeOrder());
//            Log.w("CHANGDU",inputStream.available()+"  "+rawData.length+"  "+inputStream.available());
//            inputStream.read(rawData);
//
//            int count = rawData.length/3;
//            for (int i=0;i<count;++i){
//                rawRGBAData[i*4+0]=rawData[i*3+0];
//                rawRGBAData[i*4+1]=rawData[i*3+1];
//                rawRGBAData[i*4+2]=rawData[i*3+2];
//                rawRGBAData[i*4+3]=1;
//            }
//
//            byteBuffer.put(rawRGBAData);
//            byteBuffer.position(0);
//            inputStream.close();
//            this.getAssets().close();
//
//            mOpenGLSurface.setDataBuffer(480,640,byteBuffer);
//        } catch (IOException ioException) {
//            ioException.printStackTrace();
//        }
    }
}