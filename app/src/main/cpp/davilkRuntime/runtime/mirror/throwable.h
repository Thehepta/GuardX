//
// Created by thehepta on 2024/8/20.
//

#pragma once
#include "object.h"

class String;
class MANAGED Throwable : public Object {
    HeapReference<Object> backtrace_;
    HeapReference<Throwable> cause_;
    HeapReference<String> detail_message_;
    HeapReference<Object> stack_trace_;
    HeapReference<Object> suppressed_exceptions_;
};