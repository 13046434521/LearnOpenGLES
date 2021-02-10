
#pragma once

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <android/log.h>

#define TAG "GL_UTILS"

// 加载Android Assets文件
unsigned char *loadContentFiles(AAssetManager *assetManager, const char *path);

GLuint compileShader(GLenum type, char *content);


struct RenderTime {
    long long time;
    long long lastTime;

    void *renderTime() {
    }
};

