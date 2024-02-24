#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

#ifdef DM_PLATFORM_WINDOWS
    #ifdef DM_BUILD_DLL
        #define DM_API __declspec(dllexport)
    #else
        #define DM_API __declspec(dllimport)
    #endif
#else
    #error "Deimos only supports Windows"
#endif

#ifdef DM_ENABLE_ASSERTS
    #define DM_ASSERT(x, ...) { if (!(x)) { DM_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define DM_CORE_ASSERT(x, ...) { if(!x){ { DM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define DM_ASSERT(x, ...)
    #define DM_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#endif //ENGINE_CORE_H
