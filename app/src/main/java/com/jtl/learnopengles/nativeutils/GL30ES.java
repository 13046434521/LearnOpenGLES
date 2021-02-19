package com.jtl.learnopengles.nativeutils;

import android.content.res.AssetManager;

import java.nio.ByteBuffer;

/**
 * @author：TianLong
 * @date：2021/2/7 11:51
 * @detail：
 */
public class GL30ES {
    // Used to load the 'opengles_util' library on application startup.
    static {
        System.loadLibrary("opengles_util");
    }

    public static native void glClearColor(float red, float green, float blue, float alpha);

    public static native void glClear(int type);

    public static native void onSurfaceChanged(int x, int y, int width, int height);

    public static native void initGLES(AssetManager assetManager);

    public static native void drawFrame();

    public static native void drawFrameData(int width, int height, ByteBuffer dataBuffer);
}
