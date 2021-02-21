//
// Created by TianLong on 2021/2/6.
//
#pragma once
#include <jni.h>
#include <stdio.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <android/log.h>
#include <string>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include "utils.h"
#include "Glm/glm.hpp"
#include "Glm/ext.hpp"
#define TAG "GL30ES"

void initBufferData();
struct Vertices{
    float texture[2];
    float position[4];
};