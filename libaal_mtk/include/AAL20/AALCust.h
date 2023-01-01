#ifndef __AAL_CUST_H__
#define __AAL_CUST_H__

#ifdef MTK_LOG_ENABLE
#undef MTK_LOG_ENABLE
#endif
#define MTK_LOG_ENABLE 1
#include <dlfcn.h>
#include <string.h>
#include <stdlib.h>
#include <android/log.h>

#define LOG_PREFIX "[AALCust] "

#define UNUSED_AALCUST(expr) do { (void)(expr); } while (0)

class CustParameters {
private:
    void *mLib;
    void *mLibChip; // chip level custom setting

    template <typename T>
    static void logLoadVar(const char *name, const T* var) {
        UNUSED_AALCUST(var);
        __android_log_print(ANDROID_LOG_DEBUG, "AALCust", LOG_PREFIX "Load %s", name);
    }

public:
    explicit CustParameters(const char *libPath, const char *libChipPath = NULL) {
        mLib = dlopen(libPath, RTLD_LAZY);
        if (libChipPath)
            mLibChip = dlopen(libChipPath, RTLD_LAZY);
        else
            mLibChip = NULL;
        __android_log_print(ANDROID_LOG_DEBUG, "AALCust",
            LOG_PREFIX "Load %s:%s | %s:%s", libPath, mLib? "OK":"NOT_FOUND",
            libChipPath? libChipPath:"NoChipCust", mLibChip? "OK":"NOT_FOUND");
    }

    ~CustParameters() {
        if (mLib != NULL)
            dlclose(mLib);
        if (mLibChip != NULL)
            dlclose(mLibChip);
    }

    bool isGood() {
        return (mLib != NULL) || (mLibChip != NULL);
    }

    void *getSym(const char *name)
    {
        void *addr = NULL;

        if (mLib != NULL)
            addr = dlsym(mLib, name);
        if (addr != NULL)
            return addr;
        if (mLibChip != NULL)
            addr = dlsym(mLibChip, name);

        return addr;
    }

    template <typename T>
    bool loadVar(const char *name, T* var, int index = 0) {
        if (index < 0)
            return false;

        void *symbolPtr = getSym(name);
        if (symbolPtr != NULL) {
            *var = static_cast<T*>(symbolPtr)[index];
            logLoadVar(name, var);
            return true;
        }

        return false;
    }

    template <typename T>
    bool loadArray(const char *name, T* var, unsigned int len, int index = 0) {
        if (index < 0)
            return false;

        void *symbolPtr = getSym(name);
        if (symbolPtr != NULL) {
            T *arrPtr = static_cast<T*>(symbolPtr) + len * index;
            memcpy(var, arrPtr, sizeof(T) * len);
            __android_log_print(ANDROID_LOG_DEBUG, "AALCust", LOG_PREFIX "Load %s[%d][]", name, index);
            return true;
        }

        return false;
    }

    template <typename T>
    inline T getFunction(const char *name) {
        return reinterpret_cast<T>(getSym(name));
    }
};

template <>
inline void CustParameters::logLoadVar<int>(const char *name, const int* var) {
    __android_log_print(ANDROID_LOG_DEBUG, "AALCust", LOG_PREFIX "Load %s = %d", name, *var);
}

template <>
inline void CustParameters::logLoadVar<float>(const char *name, const float* var) {
    __android_log_print(ANDROID_LOG_DEBUG, "AALCust", LOG_PREFIX "Load %s = %f", name, *var);
}

#endif
