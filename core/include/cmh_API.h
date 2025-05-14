// cmh_API.h
#pragma once

#if defined(_WIN32) || defined(_WIN64)
    #ifdef CMH_DLL
        #ifdef CMH_EXPORT
            // Building the DLL
            #define CMH_API __declspec(dllexport)
            #define CMH_DATA extern __declspec(dllexport)
        #else
            // Using the DLL
            #define CMH_API __declspec(dllimport)
            #define CMH_DATA extern __declspec(dllimport)
        #endif
    #else
        // Static linking on Windows
        #define CMH_API
        #define CMH_DATA extern
    #endif

#elif defined(__GNUC__)
    #ifdef CMH_DLL
        #ifdef CMH_EXPORT
            // Building the shared library
            #define CMH_API __attribute__((visibility("default")))
            #define CMH_DATA extern __attribute__((visibility("default")))
        #else
            // Using the shared library
            #define CMH_API
            #define CMH_DATA extern
        #endif
    #else
        // Static linking
        #define CMH_API
        #define CMH_DATA extern
    #endif

#else
    // Fallback for unknown compilers/platforms
    #define CMH_API
    #define CMH_DATA extern
#endif
