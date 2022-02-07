
#ifndef DLL
    #ifdef COMPILING_DLL
        #define DLL __declspec(dllexport)
    #else
        #define DLL __declspec(dllimport)
    #endif  
#endif