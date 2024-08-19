//
// Created by thehepta on 2024/8/19.
//

#pragma once
#include "object.h"
#include "object_array.h"

class Class;
class DexCache;
class Throwable;
class MANAGED ClassExt : public Object {
    HeapReference<Object> class_value_map_;

    // The saved error for this class being erroneous.
    HeapReference<Throwable> erroneous_state_error_;

    // Field order required by test "ValidateFieldOrderOfJavaCppUnionClasses".
    // An array containing the jfieldIDs assigned to each field in the corresponding position in the
    // classes ifields_ array or '0' if no id has been assigned to that field yet.
    HeapReference<PointerArray> instance_jfield_ids_;

    // An array containing the jmethodIDs assigned to each method in the corresponding position in
    // the classes methods_ array or '0' if no id has been assigned to that method yet.
    HeapReference<PointerArray> jmethod_ids_;

    // If set this is the Class object that was being used before a structural redefinition occurred.
    HeapReference<Class> obsolete_class_;

    HeapReference<ObjectArray<DexCache>> obsolete_dex_caches_;

    HeapReference<PointerArray> obsolete_methods_;

    HeapReference<Object> original_dex_file_;

    // An array containing the jfieldIDs assigned to each field in the corresponding position in the
    // classes sfields_ array or '0' if no id has been assigned to that field yet.
    HeapReference<PointerArray> static_jfield_ids_;

    int32_t pre_redefine_class_def_index_;

    // Native pointer to DexFile and ClassDef index of this class before it was JVMTI-redefined.
    int64_t pre_redefine_dex_file_ptr_;
};