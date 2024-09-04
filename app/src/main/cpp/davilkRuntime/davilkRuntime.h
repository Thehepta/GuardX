//
// Created by rzx on 2024/8/28.
//

#pragma once
#include "jni.h"




jobjectArray getClassLoaders(JNIEnv *env, jclass clazz) ;
jobjectArray getFilterClass(JNIEnv *env, jclass clazz) ;
void InitRuntimePart(JNIEnv *env) ;
