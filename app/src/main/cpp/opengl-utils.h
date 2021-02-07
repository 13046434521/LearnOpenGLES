//
// Created by TianLong on 2021/2/6.
//
#pragma once
#include <jni.h>
#include <stdio.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <android/log.h>
#include <string>

#define TAG "GL30ES"

void initGLES();
struct Vertices{
    float position[4];
};