#ifndef DEFINES_H
#define DEFINES_H

// 1. 优先尝试包含标准库 (Win7+, Linux, 现代编译器)
#if defined(__cplusplus) || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L)
    #include <stdint.h>
    typedef uint64_t uint64;
#else
    // 2. 针对极老旧环境 (如 Windows XP + 老版 VC)
    #ifdef _WIN32
        typedef unsigned __int64 uint64;
    #else
        // 针对老旧 Linux/Unix
        typedef unsigned long long uint64;
    #endif
#endif

// 误差阈值原子常量
#define SYNC_THRESHOLD_SECONDS 60 

#endif