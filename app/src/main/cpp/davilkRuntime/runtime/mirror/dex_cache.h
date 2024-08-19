//
// Created by thehepta on 2024/8/19.
//

#pragma once
#include "object.h"

class ClassLoader;
class String;
class MANAGED DexCache final : public Object {

    HeapReference<ClassLoader> class_loader_;
    HeapReference<String> location_;

    uint64_t dex_file_;                     // const DexFile*
                                            //
    uint64_t resolved_call_sites_;          // Array of call sites
    uint64_t resolved_fields_;              // NativeDexCacheArray holding ArtField's
    uint64_t resolved_fields_array_;        // Array of ArtField's.
    uint64_t resolved_method_types_;        // DexCacheArray holding mirror::MethodType's
    uint64_t resolved_method_types_array_;  // Array of mirror::MethodType's
    uint64_t resolved_methods_;             // NativeDexCacheArray holding ArtMethod's
    uint64_t resolved_methods_array_;       // Array of ArtMethod's
    uint64_t resolved_types_;               // DexCacheArray holding mirror::Class's
    uint64_t resolved_types_array_;         // Array of resolved types.
    uint64_t strings_;                      // DexCacheArray holding mirror::String's
    uint64_t strings_array_;                // Array of String's.
};