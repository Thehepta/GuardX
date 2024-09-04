//
// Created by rzx on 2024/8/28.
//


#include <jni.h>
#include "davilkRuntime.h"
#include "soInfo/soinfo.h"


extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_hepta_guardx_NativeUtil_getClassLoaderList(JNIEnv *env, jclass clazz) {
    // TODO: implement getClassLoaderList()
    return getClassLoaders(env,clazz);

}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_hepta_guardx_NativeUtil_getFilterClass(JNIEnv *env, jclass clazz, jobject class_names) {

    return getFilterClass(env,clazz);

}


extern "C"
JNIEXPORT jobject JNICALL
Java_com_hepta_guardx_NativeUtil_getSoinfoList(JNIEnv *env, jclass clazz) {
    // TODO: implement getSoinfoList()
    find_all_library_name();
    return nullptr;
}






jint JNI_OnLoad(JavaVM* vm, void* reserved) {

    JNIEnv* env;
    if (vm->GetEnv( (void**) &env, JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    InitRuntimePart(env);
    return JNI_VERSION_1_6;
}