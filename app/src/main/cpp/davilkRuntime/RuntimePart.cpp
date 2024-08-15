//
// Created by thehepta on 2023/8/9.
//

#include "runtime/class_linker.h"
#include "runtime/scoped_thread_state_change.h"
#include "art_method.h"
#include "Util.h"
#include <jni.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <sys/system_properties.h>
#include "FilterClassesVisitor.h"
//#define LOGV(...)  ((void)__android_log_print(ANDROID_LOG_INFO, "FreeReflect", __VA_ARGS__))
#define LOGV(...)

AndroidRunAPI *AndroidRunAPI::androidRunApi = nullptr;


class LookupClassesVisitor : public ClassLoaderVisitor {

    JNIEnv *env;
public:
    LookupClassesVisitor(JNIEnv *env, JavaVMExt *pExt) {

        int offsetOfVmExt = findOffset(env, 0, 10000, (void*) pExt);
//        LOGV("g_env offsetOfVmExt = %d",offsetOfVmExt);
        this->env = env;
        uint8_t * u_env = reinterpret_cast<uint8_t *>(env);
        jniEnvExt = reinterpret_cast<JNIEnvExt *>(u_env + offsetOfVmExt - sizeof(void *));

    }

    void Visit(ObjPtr<Object> class_loader)
    REQUIRES_SHARED(Locks::classlinker_classes_lock_, Locks::mutator_lock_) OVERRIDE {

        AndroidRunAPI* androidRunApi = AndroidRunAPI::getInstance();
        jobject classLoader_obj =  androidRunApi->AddGlobalRef( jniEnvExt->vm_,jniEnvExt->self_, class_loader);
        vec_obj.push_back(classLoader_obj);

    }

    std::vector<jobject> getVecObj(){
        return vec_obj;
    }

private:
    JNIEnvExt* jniEnvExt;
    std::vector<jobject> vec_obj;
};


void getAndroidSystemFunction(){
    AndroidRunAPI* androidRunApi = AndroidRunAPI::getInstance();

    androidRunApi->VisitClassLoaders = (void (*) (void* , void* ))resolve_elf_internal_symbol("libart.so","_ZNK3art11ClassLinker17VisitClassLoadersEPNS_18ClassLoaderVisitorE");
    androidRunApi->AddGlobalRef = (jobject (*)(void *, void *,ObjPtr<Object> ))resolve_elf_internal_symbol("libart.so","_ZN3art9JavaVMExt12AddGlobalRefEPNS_6ThreadENS_6ObjPtrINS_6mirror6ObjectEEE");

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

jobjectArray FilterClass(JNIEnv *env) {

    JavaVM *javaVM;
    env->GetJavaVM(&javaVM);
    JavaVMExt *javaVMExt = (JavaVMExt *) javaVM;

    AndroidRunAPI* androidRunApi = AndroidRunAPI::getInstance();
    LookupClassesVisitor visitor(env, javaVMExt);
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

jobjectArray getClassLoaders(JNIEnv *env) {

    JavaVM *javaVM;
    env->GetJavaVM(&javaVM);
    JavaVMExt *javaVMExt = (JavaVMExt *) javaVM;

    AndroidRunAPI* androidRunApi = AndroidRunAPI::getInstance();
    LookupClassesVisitor visitor(env, javaVMExt);
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




jobjectArray getBaseDexClassLoaders(JNIEnv *env) {

    JavaVM *javaVM;
    env->GetJavaVM(&javaVM);
    JavaVMExt *javaVMExt = (JavaVMExt *) javaVM;

    AndroidRunAPI* androidRunApi = AndroidRunAPI::getInstance();

    LookupClassesVisitor visitor(env, javaVMExt);

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
            {"getClassLoaderList", "()[Ljava/lang/ClassLoader;", (void*)getClassLoaders}
//            {"getClassFind", "()[Ljava/lang/ClassLoader;", }
    };
    env->RegisterNatives(classTest, methods, sizeof(methods)/sizeof(JNINativeMethod));



    return JNI_VERSION_1_6;
}

