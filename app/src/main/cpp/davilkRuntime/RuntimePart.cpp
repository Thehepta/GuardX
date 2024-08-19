//
// Created by thehepta on 2023/8/9.
//

#include "runtime/class_linker.h"
#include "runtime/scoped_thread_state_change.h"
#include "art_method.h"
#include <jni.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <sys/system_properties.h>
#include "FilterClassesVisitor.h"
#include "Util.h"
#include "LookupClassesVisitor.h"
//#define LOGV(...)  ((void)__android_log_print(ANDROID_LOG_INFO, "FreeReflect", __VA_ARGS__))
#define LOGV(...)

AndroidRunAPI *AndroidRunAPI::androidRunApi = nullptr;


void getAndroidSystemFunction(){
    AndroidRunAPI* androidRunApi = AndroidRunAPI::getInstance();

    androidRunApi->VisitClassLoaders = (void (*) (void* , void* ))resolve_elf_internal_symbol("libart.so","_ZNK3art11ClassLinker17VisitClassLoadersEPNS_18ClassLoaderVisitorE");
    androidRunApi->AddGlobalRef = (jobject (*)(void *, void *,ObjPtr<Object> ))resolve_elf_internal_symbol("libart.so","_ZN3art9JavaVMExt12AddGlobalRefEPNS_6ThreadENS_6ObjPtrINS_6mirror6ObjectEEE");

}

int get_heap_to_jvm_offset(){

    int apiLevel = android_get_device_api_level();
    if(apiLevel == 33) {
        return sizeof (PartialRuntime13);
    }else if(apiLevel == 32){
        return sizeof (PartialRuntime12_1);
    }else if(apiLevel == 31){
        return sizeof (PartialRuntime12);
    }else if(apiLevel == 30){
        return sizeof (PartialRuntime11);
    }else if(apiLevel == 29){
        return sizeof (PartialRuntime10);
    }else if(apiLevel == 28){
        return sizeof (PartialRuntime9);
    }else if(apiLevel == 27){
        return sizeof (PartialRuntime8_1);
    }else if(apiLevel == 26) {
        return sizeof (PartialRuntime8);
    }

}

JNIEXPORT void InitRuntimePart(JNIEnv *env) {
    JavaVM *javaVM;
    env->GetJavaVM(&javaVM);
    JavaVMExt *javaVMExt = (JavaVMExt *) javaVM;
    void *runtime = javaVMExt->runtime;
    const int MAX = 5000;
    int offsetOfVmExt = findOffset(runtime, 0, MAX, (void*) javaVMExt);
    LOGV("offsetOfVmExt: %d", offsetOfVmExt);
    int head_offset = offsetOfVmExt-get_heap_to_jvm_offset()+sizeof (void*);
    LOGV("head_offset: %d", head_offset);
    void * heap = (char*)runtime + head_offset;
    AndroidRunAPI* androidRunApi = AndroidRunAPI::getInstance();
    androidRunApi->partialRuntime = static_cast<PartialRuntime *>(heap);
    getAndroidSystemFunction();

}

jobject getFilterClass(JNIEnv *env, jclass clazz, jobject class_names) {

    JavaVM *javaVM;
    env->GetJavaVM(&javaVM);
    JavaVMExt *javaVMExt = (JavaVMExt *) javaVM;
    int offsetOfVmExt = findOffset(env, 0, 10000, (void*) javaVMExt);
    uint8_t * u_env = reinterpret_cast<uint8_t *>(env);
    JNIEnvExt* jniEnvExt = reinterpret_cast<JNIEnvExt *>(u_env + offsetOfVmExt - sizeof(void *));

    AndroidRunAPI* androidRunApi = AndroidRunAPI::getInstance();
    FilterClassesVisitor visitor(env, jniEnvExt);
    androidRunApi->VisitClassLoaders(androidRunApi->partialRuntime->class_linker_,&visitor);

    std::vector<jobject>  vectorObject =  visitor.getVecObj();
//    jclass  ClassLoader_cls = env->FindClass("java/lang/String");


    std::vector<std::string> cppStringList = {"string6", "string2", "string3"};
    // 找到 ArrayList 类
    jclass arrayListClass = env->FindClass("java/util/ArrayList");
    // 获取 ArrayList 的构造方法ID
    jmethodID arrayListConstructor = env->GetMethodID(arrayListClass, "<init>", "()V");
    // 创建一个新的 ArrayList 对象
    jobject arrayList = env->NewObject(arrayListClass, arrayListConstructor);
    // 获取 ArrayList 的 add 方法ID
    jmethodID arrayListAddMethod = env->GetMethodID(arrayListClass, "add", "(Ljava/lang/Object;)Z");
    // 遍历 C++ 字符串向量并将其添加到 ArrayList 中
    for (const std::string &cppString : cppStringList) {
        // 将 C++ 字符串转换为 Java 字符串
        jstring javaString = env->NewStringUTF(cppString.c_str());
        // 将 Java 字符串添加到 ArrayList 中
        env->CallBooleanMethod(arrayList, arrayListAddMethod, javaString);
        // 释放本地引用
        env->DeleteLocalRef(javaString);
    }
    // 释放本地引用
    env->DeleteLocalRef(arrayListClass);
    // 返回 ArrayList 对象
    return arrayList;
}

jobjectArray getClassLoaders(JNIEnv *env, jclass clazz) {

    JavaVM *javaVM;
    env->GetJavaVM(&javaVM);
    JavaVMExt *javaVMExt = (JavaVMExt *) javaVM;
    int offsetOfVmExt = findOffset(env, 0, 10000, (void*) javaVMExt);
    uint8_t * u_env = reinterpret_cast<uint8_t *>(env);
    JNIEnvExt* jniEnvExt = reinterpret_cast<JNIEnvExt *>(u_env + offsetOfVmExt - sizeof(void *));

    AndroidRunAPI* androidRunApi = AndroidRunAPI::getInstance();
    LookupClassesVisitor visitor(env, jniEnvExt);
    androidRunApi->VisitClassLoaders(androidRunApi->partialRuntime->class_linker_,&visitor);

    std::vector<jobject>  vectorObject =  visitor.getVecObj();
    jclass  ClassLoader_cls = env->FindClass("java/lang/ClassLoader");

    for (auto it = vectorObject.begin(); it != vectorObject.end(); /* no increment here */) {
        jboolean re =  env->IsInstanceOf(*it,ClassLoader_cls);
        if(!re){
            it = vectorObject.erase(it);
//            env->DeleteGlobalRef(*it);
        } else{
            ++it;
        }
    }

    jobjectArray objectArray = env->NewObjectArray(vectorObject.size(), ClassLoader_cls, NULL);

    for(int i=0;i<vectorObject.size();i++){
        env->SetObjectArrayElement(objectArray, i, vectorObject[i]);
    }
    return objectArray;
}




jobjectArray getBaseDexClassLoaders(JNIEnv *env, jclass clazz) {

    JavaVM *javaVM;
    env->GetJavaVM(&javaVM);
    JavaVMExt *javaVMExt = (JavaVMExt *) javaVM;
    int offsetOfVmExt = findOffset(env, 0, 10000, (void*) javaVMExt);
    uint8_t * u_env = reinterpret_cast<uint8_t *>(env);
    JNIEnvExt* jniEnvExt = reinterpret_cast<JNIEnvExt *>(u_env + offsetOfVmExt - sizeof(void *));
    AndroidRunAPI* androidRunApi = AndroidRunAPI::getInstance();
    LookupClassesVisitor visitor(env, jniEnvExt);
    androidRunApi->VisitClassLoaders(androidRunApi->partialRuntime->class_linker_,&visitor);

    std::vector<jobject>  vectorObject =  visitor.getVecObj();
    jclass  ClassLoader_cls = env->FindClass("dalvik/system/BaseDexClassLoader");

    for (auto it = vectorObject.begin(); it != vectorObject.end(); /* no increment here */) {
        jboolean re =  env->IsInstanceOf(*it,ClassLoader_cls);
        if(!re){
            it = vectorObject.erase(it);
        } else{
            ++it;
        }
    }

    jobjectArray objectArray = env->NewObjectArray(vectorObject.size(), ClassLoader_cls, NULL);

    for(int i=0;i<vectorObject.size();i++){
        env->SetObjectArrayElement(objectArray, i, vectorObject[i]);
    }
    return objectArray;
}


jint JNI_OnLoad(JavaVM* vm, void* reserved) {

    JNIEnv* env;
    if (vm->GetEnv( (void**) &env, JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    InitRuntimePart(env);

    jclass classTest = env->FindClass("com/hepta/guardx/NativeUtil");
    JNINativeMethod methods[]= {
            {"getBaseDexClassLoaderList", "()[Ljava/lang/ClassLoader;", (void*)getBaseDexClassLoaders},
            {"getClassLoaderList", "()[Ljava/lang/ClassLoader;", (void*)getClassLoaders},
            {"getFilterClass", "(Ljava/util/List;)Ljava/util/List;", (void*)getFilterClass}
    };
    env->RegisterNatives(classTest, methods, sizeof(methods)/sizeof(JNINativeMethod));



    return JNI_VERSION_1_6;
}
