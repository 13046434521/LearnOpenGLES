package com.jtl.learnopengles.glview;

import android.content.Context;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;

import com.jtl.learnopengles.BuildConfig;
import com.jtl.learnopengles.nativeutils.GL30ES;

import java.nio.ByteBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import static com.jtl.learnopengles.nativeutils.GL30ES.drawFrameData;

/**
 * @author：TianLong
 * @date：2021/2/6 16:36
 * @detail：
 */
public class OpenGLSurface extends GLSurfaceView implements GLSurfaceView.Renderer {
    private Context mContext;
    private int width;
    private int height;
    private ByteBuffer mByteBuffer;

    public OpenGLSurface(Context context) {
        this(context, null);
    }

    public OpenGLSurface(Context context, AttributeSet attrs) {
        super(context, attrs);
        mContext = context;
        this.setEGLContextClientVersion(2);

        //深度位数，在setRender之前调用
        this.setEGLConfigChooser(8, 8, 8, 8, 24, 0);

        this.setRenderer(this);
        this.setRenderMode(RENDERMODE_CONTINUOUSLY);

    }

    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
        GL30ES.glClearColor(0f, 0f, 0f, 1f);
        GL30ES.initGLES(mContext.getAssets());
        Log.d(BuildConfig.TAG, "onSurfaceCreated");

    }

    @Override
    public void onSurfaceChanged(GL10 gl10, int width, int height) {
        Log.d(BuildConfig.TAG, "onSurfaceChanged:" + width + ":" + height);
        GL30ES.onSurfaceChanged(0, 0, width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl10) {
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT|GLES20.GL_DEPTH_BUFFER_BIT);
//        GL30ES.drawFrame();
//        Log.d(BuildConfig.TAG,"onDrawFrame");
        if (mByteBuffer != null) {
            drawFrameData(width, height, mByteBuffer);
        }
    }

    public void setDataBuffer(int width, int height, ByteBuffer byteBuffer) {
        mByteBuffer = byteBuffer;
        this.height = height;
        this.width = width;
    }
}
