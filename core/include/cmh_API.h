#pragma once

#define CMH_JSON

#ifdef _WIN32  // Windows OS
    #ifdef CMH_DLL
        #define CMH_API __declspec(dllexport)  // Export symbols when building the DLL
        #define CMH_DATA extern __declspec(dllexport)
    #else
        #define CMH_API __declspec(dllimport)  // Import symbols when using the DLL
        #define CMH_DATA extern __declspec(dllimport)
    #endif
#elif defined(__GNUC__) && defined(NATIVE_OS_MAC)  // macOS with GCC/Clang
    #ifdef CMH_DLL
        #define CMH_API __attribute__((visibility("default")))
        #define CMH_DATA extern __attribute__((visibility("default")))
    #else
        #define CMH_API 
        #define CMH_DATA
    #endif
#else  // Other platforms (Linux, generic UNIX)
    #ifdef CMH_JSON
        #undef CMH_XML
        #define CMH_API 
        #define CMH_DATA

    #elif CMH_XML
        #undef CMH_JSON
        #define CMH_API 
        #define CMH_DATA
    #endif
        #define CMH_API 
        #define CMH_DATA

#endif
