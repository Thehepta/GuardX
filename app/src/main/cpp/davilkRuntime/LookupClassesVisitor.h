//
// Created by thehepta on 2024/8/15.
//

#pragma once
#include "RuntimePart.h"
#include "runtime/class_linker.h"
#include <vector>
#include "Util.h"
class LookupClassesVisitor : public ClassLoaderVisitor {

public:
    LookupClassesVisitor(JNIEnv *env, JNIEnvExt *pExt) {

        this->env = env;
        jniEnvExt = pExt;

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
    JNIEnv *env;

};