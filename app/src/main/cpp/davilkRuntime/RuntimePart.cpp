//
// Created by thehepta on 2023/8/9.
//

#include "runtime/class_linker.h"
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






//jobject getFilterClass(JNIEnv *env, jclass clazz, jobject class_names) {
//
//    JavaVM *javaVM;
//    env->GetJavaVM(&javaVM);
//    JavaVMExt *javaVMExt = (JavaVMExt *) javaVM;
//    int offsetOfVmExt = findOffset(env, 0, 10000, (void*) javaVMExt);
//    uint8_t * u_env = reinterpret_cast<uint8_t *>(env);
//    JNIEnvExt* jniEnvExt = reinterpret_cast<JNIEnvExt *>(u_env + offsetOfVmExt - sizeof(void *));
//
//    AndroidRunAPI* androidRunApi = AndroidRunAPI::getInstance();
//    FilterClassesVisitor visitor(env, jniEnvExt);
//    androidRunApi->VisitClassLoaders(androidRunApi->partialRuntime->class_linker_,&visitor);
//
//    std::vector<jobject>  vectorObject =  visitor.getVecObj();
////    jclass  ClassLoader_cls = env->FindClass("java/lang/String");
//
//
//    std::vector<std::string> cppStringList = {"string6", "string2", "string3"};
//    // 找到 ArrayList 类
//    jclass arrayListClass = env->FindClass("java/util/ArrayList");
//    // 获取 ArrayList 的构造方法ID
//    jmethodID arrayListConstructor = env->GetMethodID(arrayListClass, "<init>", "()V");
//    // 创建一个新的 ArrayList 对象
//    jobject arrayList = env->NewObject(arrayListClass, arrayListConstructor);
//    // 获取 ArrayList 的 add 方法ID
//    jmethodID arrayListAddMethod = env->GetMethodID(arrayListClass, "add", "(Ljava/lang/Object;)Z");
//    // 遍历 C++ 字符串向量并将其添加到 ArrayList 中
//    for (const std::string &cppString : cppStringList) {
//        // 将 C++ 字符串转换为 Java 字符串
//        jstring javaString = env->NewStringUTF(cppString.c_str());
//        // 将 Java 字符串添加到 ArrayList 中
//        env->CallBooleanMethod(arrayList, arrayListAddMethod, javaString);
//        // 释放本地引用
//        env->DeleteLocalRef(javaString);
//    }
//    // 释放本地引用
//    env->DeleteLocalRef(arrayListClass);
//    // 返回 ArrayList 对象
//    return arrayList;
//}

//jobjectArray getClassLoaders(JNIEnv *env, jclass clazz) {
//
//    JavaVM *javaVM;
//    env->GetJavaVM(&javaVM);
//    JavaVMExt *javaVMExt = (JavaVMExt *) javaVM;
//    int offsetOfVmExt = findOffset(env, 0, 10000, (void*) javaVMExt);
//    uint8_t * u_env = reinterpret_cast<uint8_t *>(env);
//    JNIEnvExt* jniEnvExt = reinterpret_cast<JNIEnvExt *>(u_env + offsetOfVmExt - sizeof(void *));
//
//    AndroidRunAPI* androidRunApi = AndroidRunAPI::getInstance();
//    LookupClassesVisitor visitor(env, jniEnvExt);
//    androidRunApi->VisitClassLoaders(androidRunApi->partialRuntime->class_linker_,&visitor);
//
//    std::vector<jobject>  vectorObject =  visitor.getVecObj();
//    jclass  ClassLoader_cls = env->FindClass("java/lang/ClassLoader");
//
//    for (auto it = vectorObject.begin(); it != vectorObject.end(); /* no increment here */) {
//        jboolean re =  env->IsInstanceOf(*it,ClassLoader_cls);
//        if(!re){
//            it = vectorObject.erase(it);
////            env->DeleteGlobalRef(*it);
//        } else{
//            ++it;
//        }
//    }
//
//    jobjectArray objectArray = env->NewObjectArray(vectorObject.size(), ClassLoader_cls, NULL);
//
//    for(int i=0;i<vectorObject.size();i++){
//        env->SetObjectArrayElement(objectArray, i, vectorObject[i]);
//    }
//    return objectArray;
//}




//jobjectArray getBaseDexClassLoaders(JNIEnv *env, jclass clazz) {
//
//    JavaVM *javaVM;
//    env->GetJavaVM(&javaVM);
//    JavaVMExt *javaVMExt = (JavaVMExt *) javaVM;
//    int offsetOfVmExt = findOffset(env, 0, 10000, (void*) javaVMExt);
//    uint8_t * u_env = reinterpret_cast<uint8_t *>(env);
//    JNIEnvExt* jniEnvExt = reinterpret_cast<JNIEnvExt *>(u_env + offsetOfVmExt - sizeof(void *));
//    AndroidRunAPI* androidRunApi = AndroidRunAPI::getInstance();
//    LookupClassesVisitor visitor(env, jniEnvExt);
//    androidRunApi->VisitClassLoaders(androidRunApi->partialRuntime->class_linker_,&visitor);
//
//    std::vector<jobject>  vectorObject =  visitor.getVecObj();
//    jclass  ClassLoader_cls = env->FindClass("dalvik/system/BaseDexClassLoader");
//
//    for (auto it = vectorObject.begin(); it != vectorObject.end(); /* no increment here */) {
//        jboolean re =  env->IsInstanceOf(*it,ClassLoader_cls);
//        if(!re){
//            it = vectorObject.erase(it);
//        } else{
//            ++it;
//        }
//    }
//
//    jobjectArray objectArray = env->NewObjectArray(vectorObject.size(), ClassLoader_cls, NULL);
//
//    for(int i=0;i<vectorObject.size();i++){
//        env->SetObjectArrayElement(objectArray, i, vectorObject[i]);
//    }
//    return objectArray;
//}


//jint JNI_OnLoad(JavaVM* vm, void* reserved) {
//
//    JNIEnv* env;
//    if (vm->GetEnv( (void**) &env, JNI_VERSION_1_6) != JNI_OK) {
//        return -1;
//    }
//    InitRuntimePart(env);
//
//    jclass classTest = env->FindClass("com/hepta/guardx/NativeUtil");
//    JNINativeMethod methods[]= {
//            {"getBaseDexClassLoaderList", "()[Ljava/lang/ClassLoader;", (void*)getBaseDexClassLoaders},
//            {"getClassLoaderList", "()[Ljava/lang/ClassLoader;", (void*)getClassLoaders},
//            {"getFilterClass", "(Ljava/util/List;)Ljava/util/List;", (void*)getFilterClass}
//    };
//    env->RegisterNatives(classTest, methods, sizeof(methods)/sizeof(JNINativeMethod));
//
//
//
//    return JNI_VERSION_1_6;
//}
