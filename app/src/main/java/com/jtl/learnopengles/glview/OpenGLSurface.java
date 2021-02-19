package com.jtl.learnopengles.glview;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLES20;
import android.opengl.GLES30;
import android.opengl.GLSurfaceView;
import android.os.Build;
import android.support.annotation.RequiresApi;
import android.util.AttributeSet;
import android.util.Log;

import com.jtl.learnopengles.BuildConfig;
import com.jtl.learnopengles.MainActivity;
import com.jtl.learnopengles.R;
import com.jtl.learnopengles.nativeutils.GL30ES;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * @author：TianLong
 * @date：2021/2/6 16:36
 * @detail：
 */
public class OpenGLSurface extends GLSurfaceView implements GLSurfaceView.Renderer {
    private Context mContext;
    private Bitmap mBitmap;
    private ByteBuffer mDataBuffer;
    private int width;
    private int height;
    public OpenGLSurface(Context context) {
        this(context,null);
    }

    public OpenGLSurface(Context context, AttributeSet attrs) {
        super(context, attrs);
        mContext = context;
        this.setEGLContextClientVersion(2);

        //深度位数，在setRender之前调用
        this.setEGLConfigChooser(8, 8, 8, 8, 24, 0);

        this.setRenderer(this);
        this.setRenderMode(RENDERMODE_CONTINUOUSLY);
        Bitmap bitmap = BitmapFactory.decodeResource(context.getResources(), R.mipmap.gltest);
        width = bitmap.getWidth();
        height = bitmap.getHeight();
        Log.w("CESHI ",bitmap.getConfig().name()+"  "+width+"  "+height);
        mDataBuffer = ByteBuffer.allocateDirect(width*height*4).order(ByteOrder.nativeOrder());
        bitmap.copyPixelsToBuffer(mDataBuffer);
        mDataBuffer.position(0);
    }

    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
        GL30ES.glClearColor(1f,1f,1f,1);
        Log.d(BuildConfig.TAG,"onSurfaceCreated");
        GL30ES.initGLES(mContext.getAssets());
        checkGLError("错了？");
    }

    @Override
    public void onSurfaceChanged(GL10 gl10, int width, int height) {
        Log.d(BuildConfig.TAG,"onSurfaceChanged:"+width+":"+height);
        GL30ES.onSurfaceChanged(0,0,width ,height );
//        GLES20.glViewport(0,0,i,i1);
    }

    @Override
    public void onDrawFrame(GL10 gl10) {
        GL30ES.glClear(GLES20.GL_COLOR_BUFFER_BIT);
//        GL30ES.drawFrame();

        GL30ES.drawFrameData(width,height,mDataBuffer);
//        Log.d(BuildConfig.TAG,"onDrawFrame");
        checkGLError("错了？");
    }

    public static void checkGLError(String label) {
        int lastError = GLES20.GL_NO_ERROR;
        // Drain the queue of all errors.
        int error;
        while ((error = GLES20.glGetError()) != GLES20.GL_NO_ERROR) {
            Log.e("", label + ": glError " + error);
            lastError = error;
        }
        if (lastError != GLES20.GL_NO_ERROR) {
            throw new RuntimeException(label + ": glError " + lastError);
        }
    }
}
