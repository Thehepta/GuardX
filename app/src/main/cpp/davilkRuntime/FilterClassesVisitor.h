//
// Created by rzx on 2024/8/15.
//

#pragma once
#include "RuntimePart.h"
#include "runtime/class_linker.h"
#include "runtime/scoped_thread_state_change.h"
#include "art_method.h"
#include "Util.h"
#include <vector>
class FilterClassesVisitor : public ClassLoaderVisitor {

    JNIEnv *env;
    jclass  cls;
public:
    FilterClassesVisitor(JNIEnv *env, JavaVMExt *pExt) {

        int offsetOfVmExt = findOffset(env, 0, 10000, (void*) pExt);
        this->env = env;
        uint8_t * u_env = reinterpret_cast<uint8_t *>(env);
        jniEnvExt = reinterpret_cast<JNIEnvExt *>(u_env + offsetOfVmExt - sizeof(void *));
        jobject ClassLoader_cls = env->FindClass("java/lang/Class");
        this->cls = (jclass)env->NewGlobalRef(ClassLoader_cls);

    }

    void Visit(ObjPtr<Object> class_loader)
    REQUIRES_SHARED(Locks::classlinker_classes_lock_, Locks::mutator_lock_) OVERRIDE {

        AndroidRunAPI* androidRunApi = AndroidRunAPI::getInstance();
        jobject classLoader_obj =  androidRunApi->AddGlobalRef( jniEnvExt->vm_,jniEnvExt->self_, class_loader);
        jboolean re =  env->IsInstanceOf(cls,classLoader_obj);

        vec_obj.push_back(classLoader_obj);

    }

    std::vector<jobject> getVecObj(){
        return vec_obj;
    }

private:
    JNIEnvExt* jniEnvExt;
    std::vector<jobject> vec_obj;
};


