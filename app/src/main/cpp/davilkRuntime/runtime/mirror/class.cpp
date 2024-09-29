//
// Created by rzx on 2024/9/4.
//
#include "class.h"

Class_StubFun* Class::classStubFun = new Class_StubFun();

std::string Class::PrettyDescriptor() {
    return classStubFun->PrettyDescriptor(this);
}

