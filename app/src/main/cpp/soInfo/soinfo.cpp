#include "jni.h"
#include "vector"
#include "elf_symbol_resolver.h"

#include "android/log.h"

#define LOGV(...)  ((void)__android_log_print(ANDROID_LOG_INFO, "FilterClassesVisitor", __VA_ARGS__))


#define soinfo uintptr_t


soinfo* (*solist_get_head)() = (soinfo* (*)()) linkerResolveElfInternalSymbol(
        get_android_linker_path(), "__dl__Z15solist_get_headv");

soinfo* (*solist_get_somain)() = (soinfo* (*)()) linkerResolveElfInternalSymbol(
        get_android_linker_path(), "__dl__Z17solist_get_somainv");

char* (*soinfo_get_soname)(soinfo*) = (char* (*)(soinfo*)) linkerResolveElfInternalSymbol(
        get_android_linker_path(), "__dl__ZNK6soinfo10get_sonameEv");





//通过动态计算结构内部成员的位置，循环找到soinfo 内部的next的位置，然后通过next进行遍历
void find_all_library_name(){
    std::vector<void *> linker_solist;

    static uintptr_t *solist_head = NULL;
    if (!solist_head)
        solist_head = (uintptr_t *)solist_get_head();


    static uintptr_t somain = 0;

    if (!somain)
        somain = (uintptr_t)solist_get_somain();

    // Generate the name for an offset.
#define PARAM_OFFSET(type_, member_) __##type_##__##member_##__offset_
#define STRUCT_OFFSET PARAM_OFFSET
    int STRUCT_OFFSET(solist, next) = 0;
    for (size_t i = 0; i < 1024 / sizeof(void *); i++) {
        if (*(uintptr_t *)((uintptr_t)solist_head + i * sizeof(void *)) == somain) {
            STRUCT_OFFSET(solist, next) = i * sizeof(void *);
            break;
        }
    }

    linker_solist.push_back(solist_head);

    uintptr_t sonext = 0;
    sonext = *(uintptr_t *)((uintptr_t)solist_head + STRUCT_OFFSET(solist, next));
    while (sonext) {
        linker_solist.push_back((void *)sonext);
        sonext = *(uintptr_t *)((uintptr_t)sonext + STRUCT_OFFSET(solist, next));
        if(sonext == 0){
            continue;
        }
        char* ret_name = soinfo_get_soname(reinterpret_cast<soinfo *>(sonext));
        LOGV("soinfo addr:%p %s",sonext,ret_name);
    }

    return ;
}
