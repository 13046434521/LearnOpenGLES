package com.jtl.learnopengles.glview;

import android.content.Context;
import android.opengl.GLES20;
import android.opengl.GLES30;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;

import com.jtl.learnopengles.BuildConfig;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * @author：TianLong
 * @date：2021/2/6 16:36
 * @detail：
 */
class OpenGLSurface extends GLSurfaceView implements GLSurfaceView.Renderer {

    public OpenGLSurface(Context context) {
        this(context,null);
    }

    public OpenGLSurface(Context context, AttributeSet attrs) {
        super(context, attrs);

        this.setEGLContextClientVersion(2);

        //深度位数，在setRender之前调用
        this.setEGLConfigChooser(8, 8, 8, 8, 24, 0);

        this.setRenderer(this);
        this.setRenderMode(RENDERMODE_CONTINUOUSLY);
    }

    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
        GLES20.glClearColor(0.1f,0.4f,0.6f,1f);
        Log.d(BuildConfig.TAG,"onSurfaceCreated");
    }

    @Override
    public void onSurfaceChanged(GL10 gl10, int i, int i1) {
        Log.d(BuildConfig.TAG,"onSurfaceChanged:"+i+":"+i1);
        GLES20.glViewport(i/4,i1/4,i/2,i1/2);
    }

    @Override
    public void onDrawFrame(GL10 gl10) {
        GLES20.glClear(GLES30.GL_COLOR_BUFFER_BIT);
        Log.d(BuildConfig.TAG,"onDrawFrame");
    }
}
