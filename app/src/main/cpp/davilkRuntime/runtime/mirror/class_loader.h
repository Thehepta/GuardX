//
// Created by thehepta on 2024/8/19.
//

#pragma once
#include "object.h"
#define ATTRIBUTE_UNUSED __attribute__((__unused__))

class MANAGED ClassLoader : public Object {

    HeapReference<Object> packages_;
    HeapReference<ClassLoader> parent_;
    HeapReference<Object> proxyCache_;
    // Native pointer to class table, need to zero this out when image writing.
    uint32_t padding_ ATTRIBUTE_UNUSED;
    uint64_t allocator_;
    uint64_t class_table_;
};
