//
// Created by thehepta on 2023/8/12.
//

#pragma once
#include <atomic>
#include "runtime/macro.h"
template<class MirrorType>
class MANAGED HeapReference {

private:
    std::atomic<uint32_t> reference_;

};

