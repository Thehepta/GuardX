//
// Created by rzx on 2024/8/15.
//


#include "FilterClassesVisitor.h"
#include "runtime/mirror/class.h"

#include "android/log.h"
#define LOGV(...)  ((void)__android_log_print(ANDROID_LOG_INFO, "FilterClassesVisitor", __VA_ARGS__))

bool FilterClassesVisitor::operator()(ObjPtr<Class> klass) {
    std::string clsDes = klass->PrettyDescriptor();
    LOGV("clsName %s",clsDes.c_str());
//    int a = 10;
//    LOGV("clsName %p",klass);
    return true;
}

