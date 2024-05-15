#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

#include <memory>

#ifdef DM_PLATFORM_WINDOWS
#if DM_DYNAMIC_LINK
    #ifdef DM_BUILD_DLL
        #define DM_API __declspec(dllexport)
    #else
        #define DM_API __declspec(dllimport)
    #endif
#else
    #define DM_API
#endif
    #ifdef DM_ENABLE_ASSERTS
        #define DM_ASSERT(x, ...) { if (!(x)) { DM_ERROR("Assertion Failed: {0}", __VA_ARGS__);__debugbreak(); } }
        #define DM_CORE_ASSERT(x, ...) { if(!(x)) { DM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #else
        #define DM_ASSERT(x, ...)
        #define DM_CORE_ASSERT(x, ...)
#endif
#elif DM_PLATFORM_LINUX
#if DM_DYNAMIC_BUILD
    #ifdef DM_BUILD_DLL
        #define DM_API __attribute__((visibility("default")))
    #else
        #define DM_API __attribute__((visibility("default")))
    #endif
#else
#define DM_API
#endif
    #ifdef DM_ENABLE_ASSERTS
        #define DM_ASSERT(x, ...) { if (!(x)) { DM_ERROR("Assertion Failed: {0}", __VA_ARGS__); __builtin_trap(); } }
        #define DM_CORE_ASSERT(x, ...) { if(!(x)) { DM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __builtin_trap(); } }
    #else
        #define DM_ASSERT(x, ...)
        #define DM_CORE_ASSERT(x, ...)
#endif
#endif


#define BIT(x) (1 << x)

namespace Deimos {
    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T>
    using Ref = std::shared_ptr<T>;
}

#endif //ENGINE_CORE_H
