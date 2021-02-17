package com.jtl.learnopengles.glview;

import android.content.Context;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;

import com.jtl.learnopengles.BuildConfig;
import com.jtl.learnopengles.nativeutils.GL30ES;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * @author：TianLong
 * @date：2021/2/6 16:36
 * @detail：
 */
class OpenGLSurface extends GLSurfaceView implements GLSurfaceView.Renderer {
    private Context mContext;
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

    }

    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
        GL30ES.initGLES(mContext.getAssets());
        GL30ES.glClearColor(0.1f,1f,0.1f,1);
        Log.d(BuildConfig.TAG,"onSurfaceCreated");

    }

    @Override
    public void onSurfaceChanged(GL10 gl10, int i, int i1) {
        Log.d(BuildConfig.TAG,"onSurfaceChanged:"+i+":"+i1);
        GL30ES.onSurfaceChanged(i/4,i1/4,i/2,i1/2);
    }

    @Override
    public void onDrawFrame(GL10 gl10) {
        GL30ES.glClear(GLES20.GL_COLOR_BUFFER_BIT);
        GL30ES.drawFrame();
//        Log.d(BuildConfig.TAG,"onDrawFrame");
    }
}
