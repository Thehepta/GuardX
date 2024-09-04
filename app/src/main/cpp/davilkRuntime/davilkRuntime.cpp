//
// Created by rzx on 2024/8/28.
//

#include "davilkRuntime.h"
#include "LookupClassesVisitor.h"
#include "FilterClassesVisitor.h"

#define LOGV(...)


AndroidRunAPI *AndroidRunAPI::androidRunApi = nullptr;

jobjectArray getClassLoaders(JNIEnv *env, jclass clazz) {

    JavaVM *javaVM;
    env->GetJavaVM(&javaVM);
    auto *javaVMExt = (JavaVMExt *) javaVM;
    int offsetOfVmExt = findOffset(env, 0, 10000, (void*) javaVMExt);
    auto * u_env = reinterpret_cast<uint8_t *>(env);
    auto* jniEnvExt = reinterpret_cast<JNIEnvExt *>(u_env + offsetOfVmExt - sizeof(void *));

    AndroidRunAPI* androidRunApi = AndroidRunAPI::getInstance();
    LookupClassesVisitor visitor(env, jniEnvExt);
    androidRunApi->VisitClassLoaders(androidRunApi->partialRuntime->class_linker_,&visitor);

    auto  vectorObject =  visitor.getVecObj();
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

    jobjectArray objectArray = env->NewObjectArray(vectorObject.size(), ClassLoader_cls, nullptr);

    for(int i=0;i<vectorObject.size();i++){
        env->SetObjectArrayElement(objectArray, i, vectorObject[i]);
    }
    return objectArray;
}

jobjectArray getFilterClass(JNIEnv *env, jclass clazz) {

    JavaVM *javaVM;
    env->GetJavaVM(&javaVM);
    JavaVMExt *javaVMExt = (JavaVMExt *) javaVM;
    int offsetOfVmExt = findOffset(env, 0, 10000, (void*) javaVMExt);
    uint8_t * u_env = reinterpret_cast<uint8_t *>(env);
    JNIEnvExt* jniEnvExt = reinterpret_cast<JNIEnvExt *>(u_env + offsetOfVmExt - sizeof(void *));

    AndroidRunAPI* androidRunApi = AndroidRunAPI::getInstance();
    FilterClassesVisitor visitor(env, jniEnvExt);
    androidRunApi->VisitClassLoaders(androidRunApi->partialRuntime->class_linker_,&visitor);

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
    return nullptr;
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


void getAndroidSystemFunction(){
    AndroidRunAPI* androidRunApi = AndroidRunAPI::getInstance();

    androidRunApi->VisitClasses = (void (*) (void* , void* ))resolve_elf_internal_symbol("libart.so","_ZN3art11ClassLinker12VisitClassesEPNS_12ClassVisitorE");
    androidRunApi->VisitClassLoaders = (void (*) (void* , void* ))resolve_elf_internal_symbol("libart.so","_ZNK3art11ClassLinker17VisitClassLoadersEPNS_18ClassLoaderVisitorE");
    androidRunApi->AddGlobalRef = (jobject (*)(void *, void *,ObjPtr<Object> ))resolve_elf_internal_symbol("libart.so","_ZN3art9JavaVMExt12AddGlobalRefEPNS_6ThreadENS_6ObjPtrINS_6mirror6ObjectEEE");

}


void InitRuntimePart(JNIEnv *env) {
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