//
// Created by thehepta on 2024/8/19.
//
//http://aospxref.com/android-13.0.0_r3/xref/art/runtime/mirror/string.h
#pragma once
#include "object.h"

class MANAGED String final : public Object {

    int32_t count_;

    uint32_t hash_code_;

    // Compression of all-ASCII into 8-bit memory leads to usage one of these fields
    union {
        uint16_t value_[0];
        uint8_t value_compressed_[0];
    };
};