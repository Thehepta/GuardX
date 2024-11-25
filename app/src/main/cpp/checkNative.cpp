//
// Created by chic on 2024/11/8.
//

#include <linux/un.h>
#include <sys/socket.h>
#include <unistd.h>
#include <android/log.h>
#include "string"
#include "artmethod_native_hook.h"
#include <jni.h>
#include <dlfcn.h>
#include <asm-generic/mman.h>
#include <sys/sysmacros.h>
#include "lsplt/include/lsplt.hpp"
#include "sys/types.h"
#include "vector"
#include "array"
#include <cinttypes>
#include "pthread.h"

# define LOG_TAG "CheceNative"




#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)




bool art_method_hook_init(JNIEnv *env) {

    jclass Process_cls = env->FindClass("com/hepta/guardx/Tool/utils/NativeUtil");
    jmethodID javamethod = env->GetStaticMethodID(Process_cls, "lsplt","(Ljava/lang/reflect/Member;)Z");
    void *libandroid_runtime = dlopen("libGuardX.so", RTLD_NOW);
    uintptr_t getUidForName = reinterpret_cast<uintptr_t>(dlsym(libandroid_runtime,"Java_com_hepta_guardx_Tool_utils_NativeUtil_zygiskCheck"));
    INIT_HOOK_PlatformABI(env, Process_cls, javamethod, (uintptr_t *) getUidForName, 0x109);

    uintptr_t art_javamethod_method = GetArtMethod(env, Process_cls, javamethod);
    uintptr_t native_art_art_javamethod_method = GetOriginalNativeFunction((uintptr_t *) art_javamethod_method);

    if (native_art_art_javamethod_method == getUidForName) {
        return true;
    } else {
        return false;
    }
}


static void hook_register(dev_t dev, ino_t inode, const char *symbol, void *new_func, void **old_func) {
    if (!lsplt::RegisterHook(dev, inode, symbol, new_func, old_func)) {
        LOGE("Failed to register plt_hook \"%s\"\n", symbol);
        return;
    }
}





void artMethodChect(JNIEnv *env,jobject nativeSpecializeAppProcess_method) {

    art_method_hook_init(env);
    uintptr_t  jmethodArtmethod = GetArtMethod(env, nullptr, nativeSpecializeAppProcess_method);
    uintptr_t native_art_javamethod_method = GetOriginalNativeFunction((uintptr_t *)jmethodArtmethod);
    LOGE("native_art_javamethod_method %lx",native_art_javamethod_method);
    LOGE("native_art_javamethod_method %lx",native_art_javamethod_method);

}

struct MapInfo {
    /// \brief The start address of the memory region.
    uintptr_t start;
    /// \brief The end address of the memory region.
    uintptr_t end;
    /// \brief The permissions of the memory region. This is a bit mask of the following values:
    /// - PROT_READ
    /// - PROT_WRITE
    /// - PROT_EXEC
    uint8_t perms;
    /// \brief Whether the memory region is private.
    bool is_private;
    /// \brief The offset of the memory region.
    uintptr_t offset;
    /// \brief The device number of the memory region.
    /// Major can be obtained by #major()
    /// Minor can be obtained by #minor()
    dev_t dev;
    /// \brief The inode number of the memory region.
    ino_t inode;
    /// \brief The path of the memory region.
    std::string path;


};

 std::vector<MapInfo> Scan(pid_t pid) {
    constexpr static auto kPermLength = 5;
    constexpr static auto kMapEntry = 7;
    std::vector<MapInfo> info;
    auto path = "/proc/" + std::to_string(pid) + "/maps";
    auto maps = std::unique_ptr<FILE, decltype(&fclose)>{fopen(path.c_str(), "r"), &fclose};
    if (maps) {
        char *line = nullptr;
        size_t len = 0;
        ssize_t read;
        while ((read = getline(&line, &len, maps.get())) > 0) {
            line[read - 1] = '\0';
            uintptr_t start = 0;
            uintptr_t end = 0;
            uintptr_t off = 0;
            ino_t inode = 0;
            unsigned int dev_major = 0;
            unsigned int dev_minor = 0;
            std::array<char, kPermLength> perm{'\0'};
            int path_off;
            if (sscanf(line, "%" PRIxPTR "-%" PRIxPTR " %4s %" PRIxPTR " %x:%x %lu %n%*s", &start,
                    &end, perm.data(), &off, &dev_major, &dev_minor, &inode,
                    &path_off) != kMapEntry) {
                continue;
            }
            while (path_off < read && isspace(line[path_off])) path_off++;
            auto ref = MapInfo{start, end, 0, perm[3] == 'p', off,
                               static_cast<dev_t>(makedev(dev_major, dev_minor)),
                               inode, line + path_off};
            if (perm[0] == 'r') ref.perms |= PROT_READ;
            if (perm[1] == 'w') ref.perms |= PROT_WRITE;
            if (perm[2] == 'x') ref.perms |= PROT_EXEC;
            info.emplace_back(ref);
        }
        free(line);
    }
    return info;
}




static bool hook_commit() {
    if (lsplt::CommitHook()) {
        return true;
    } else {
        LOGE("plt_hook failed\n");
        return false;
    }
}


#define PLT_HOOK_REGISTER_SYM(DEV, INODE, SYM, NAME) \
    hook_register(DEV, INODE, SYM, (void*) new_##NAME, (void **) &old_##NAME)

#define PLT_HOOK_REGISTER(DEV, INODE, NAME) \
    PLT_HOOK_REGISTER_SYM(DEV, INODE, #NAME, NAME)


#define DCL_HOOK_FUNC(ret, func, ...) \
ret (*old_##func)(__VA_ARGS__);       \
ret new_##func(__VA_ARGS__)

//DCL_HOOK_FUNC


int new_pthread_attr_destroy( void *target);
int (*old_pthread_attr_destroy)( void *target) ;

static void unhook_functions() {

    ino_t art_inode = 0;
    dev_t art_dev = 0;
    for (auto &map : Scan(getpid())) {
        if (map.path.find("/libGuardX.so") != std::string_view::npos) {
            art_inode = map.inode;
            art_dev = map.dev;
            break;
        }
    }
    hook_register(art_dev, art_inode, "pthread_attr_destroy", (void*)old_pthread_attr_destroy,nullptr);

    hook_commit();

    return;
}



int new_pthread_attr_destroy( void *target) {
//    int res = old_pthread_attr_destroy((pthread_attr_t *)target);

    // Only perform unloading on the main thread
//    if (gettid() != getpid())
//        return res;

    LOGE("pthread_attr_destroy\n");
    unhook_functions();
//    if (should_unmap_zygisk) {
//        unhook_functions();
//        if (should_unmap_zygisk) {
//            // Because both `pthread_attr_destroy` and `dlclose` have the same function signature,
//            // we can use `musttail` to let the compiler reuse our stack frame and thus
//            // `dlclose` will directly return to the caller of `pthread_attr_destroy`.
//            [[clang::musttail]] return dlclose(self_handle);
//        }
//    }

    return -1;
}


static void hook_unloader() {
    ino_t art_inode = 0;
    dev_t art_dev = 0;
    for (auto &map : Scan(getpid())) {
        if (map.path.find("/libGuardX.so") != std::string_view::npos) {
            art_inode = map.inode;
            art_dev = map.dev;
            break;
        }
    }
    hook_register(art_dev, art_inode, "pthread_attr_destroy", (void*)new_pthread_attr_destroy,(void**)&old_pthread_attr_destroy);

    hook_commit();

    return;
}

void lspltTest(JNIEnv *env, jobject nativeSpecializeAppProcess_method) {

    hook_unloader();
    pthread_attr_destroy((pthread_attr_t *) "");
}
