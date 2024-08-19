//
// Created by rzx on 2024/8/15.
//

#pragma once
#include "RuntimePart.h"
#include <android/log.h>

template<typename T>
int findOffset(void *start, int regionStart, int regionEnd, T value) {

    if (nullptr == start || regionEnd <= 0 || regionStart < 0) {
        return -1;
    }
    char *c_start = (char *) start;

    for (int i = regionStart; i < regionEnd; i += 4) {
        T *current_value = (T *) (c_start + i);
        if (value == *current_value) {
//            LOGV("found offset: %d", i);
            return i;
        }
    }
    return -2;
}

