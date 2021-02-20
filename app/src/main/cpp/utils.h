#include <limits.h>

#pragma once

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <android/log.h>

#define TAG "GL_UTILS"

// 加载Android Assets文件
unsigned char *loadContentFiles(AAssetManager *assetManager, const char *path);

GLuint compileShader(char* name,GLenum type, char *content);

GLuint createProgram(GLuint vertexShader,GLuint fragmentShader);

struct RenderTime {
    long long time;
    long long lastTime;

    void *renderTime() {
    }
};

