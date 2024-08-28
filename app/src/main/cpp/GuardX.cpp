//
// Created by rzx on 2024/8/28.
//


#include <jni.h>
#include "davilkRuntime.h"
extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_hepta_guardx_NativeUtil_getClassLoaderList(JNIEnv *env, jclass clazz) {
    // TODO: implement getClassLoaderList()
    return getClassLoaders(env,clazz);

}


jint JNI_OnLoad(JavaVM* vm, void* reserved) {

    JNIEnv* env;
    if (vm->GetEnv( (void**) &env, JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    InitRuntimePart(env);
    return JNI_VERSION_1_6;
}