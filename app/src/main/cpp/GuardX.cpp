//
// Created by rzx on 2024/8/28.
//


#include <jni.h>
#include "davilkRuntime.h"
#include "soInfo/soinfo.h"
#include <android/log.h>

#include "checkNative.h"



jint JNI_OnLoad(JavaVM* vm, void* reserved) {

    JNIEnv* env;
    if (vm->GetEnv( (void**) &env, JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    InitRuntimePart(env);
    return JNI_VERSION_1_6;
}

extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_hepta_guardx_Tool_utils_NativeUtil_getClassLoaderList(JNIEnv *env, jclass clazz) {
    // TODO: implement getClassLoaderList()
    return getClassLoaders(env,clazz);
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_hepta_guardx_Tool_utils_NativeUtil_getFilterClass(JNIEnv *env, jclass clazz,
                                                           jobject class_names) {
    return getFilterClass(env,clazz);
}
extern "C"
JNIEXPORT jobject JNICALL
Java_com_hepta_guardx_Tool_utils_NativeUtil_getSoinfoList(JNIEnv *env, jclass clazz) {
    find_all_library_name();
    return nullptr;
}
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_hepta_guardx_Tool_utils_NativeUtil_lsplt(JNIEnv *env, jclass clazz, jobject nativeSpecializeAppProcess_method) {
    // TODO: implement zygiskCheck()
    lspltTest(env, nativeSpecializeAppProcess_method);
    return true;
}