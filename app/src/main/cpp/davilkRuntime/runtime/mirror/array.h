//
// Created by thehepta on 2024/8/20.
//
#pragma once
#include "object.h"

#define ATTRIBUTE_UNUSED __attribute__((__unused__))


class MANAGED Array : public Object {

    // The number of array elements.
    // We only use the field indirectly using the LengthOffset() method.
    int32_t length_ ATTRIBUTE_UNUSED;
    // Marker for the data (used by generated code)
    // We only use the field indirectly using the DataOffset() method.
    uint32_t first_element_[0] ATTRIBUTE_UNUSED;
};


class PointerArray : public Array {

};

