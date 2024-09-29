//
// Created by rzx on 2024/8/15.
//

#pragma once
#include "RuntimePart.h"
#include "runtime/class_linker.h"
#include "runtime/scoped_thread_state_change.h"
#include "art_method.h"
#include <vector>


class FilterClassesVisitor : public ClassVisitor {

//    JNIEnvExt
public:
    explicit FilterClassesVisitor(JNIEnv *env,  JNIEnvExt *pExt) {

        this->env = env;
        jniEnvExt = pExt;
        jobject ClassLoader_cls = env->FindClass("java/lang/Class");
        this->cls = (jclass)env->NewGlobalRef(ClassLoader_cls);

    }

    bool operator()(ObjPtr<Class> klass)  override REQUIRES_SHARED(Locks::mutator_lock_);


    std::vector<jobject> getVecObj(){
        return vec_obj;
    }
    ~FilterClassesVisitor() override{
        env->DeleteGlobalRef(cls);
    }

private:
    JNIEnvExt* jniEnvExt;
    std::vector<jobject> vec_obj;
    JNIEnv *env;
    jclass  cls;

};


