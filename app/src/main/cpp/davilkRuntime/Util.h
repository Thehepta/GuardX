//
// Created by rzx on 2024/8/15.
//

#pragma once
#include "RuntimePart.h"
#include <android/log.h>

#define LOGV(...)  ((void)__android_log_print(ANDROID_LOG_INFO, "davlikRuntime", __VA_ARGS__))




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


int get_heap_to_jvm_offset(){

    int apiLevel = android_get_device_api_level();
    if(apiLevel == 33) {
        return sizeof (PartialRuntime13);
    }else if(apiLevel == 32){
        return sizeof (PartialRuntime12_1);
    }else if(apiLevel == 31){
        return sizeof (PartialRuntime12);
    }else if(apiLevel == 30){
        return sizeof (PartialRuntime11);
    }else if(apiLevel == 29){
        return sizeof (PartialRuntime10);
    }else if(apiLevel == 28){
        return sizeof (PartialRuntime9);
    }else if(apiLevel == 27){
        return sizeof (PartialRuntime8_1);
    }else if(apiLevel == 26) {
        return sizeof (PartialRuntime8);
    }

}