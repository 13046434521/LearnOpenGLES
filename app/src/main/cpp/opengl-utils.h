//
// Created by TianLong on 2021/2/6.
//
#pragma once
#include <jni.h>
#include <stdio.h>
#include <android/log.h>
#include <string>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include "utils.h"
#include "Glm/glm.hpp"
#include "Glm/ext.hpp"
#define TAG "GL30ES"

void initBufferData();
void initTexture();
struct Vertices{
    float position[4];
    float texture[4];
};