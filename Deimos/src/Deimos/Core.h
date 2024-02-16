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



class Core {

};


#endif //ENGINE_CORE_H
