#include "Common.h"
#ifdef _WIN32
    #include <windows.h>
#else
    #include <time.h>
#endif

// --- 补回被遗漏的函数：获取绝对系统时间 ---
uint64 getSystemRawSeconds(int& out_micro) {
#ifdef _WIN32
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    
    ULARGE_INTEGER li;
    li.LowPart = ft.dwLowDateTime;
    li.HighPart = ft.dwHighDateTime;
    
    // 1601年到1970年的100纳秒数偏移量
    uint64 unix100ns = li.QuadPart - 116444736000000000ULL;
    
    // 返回秒数
    uint64 unixSec = unix100ns / 10000000ULL;
    // 提取微秒 (1微秒 = 10 * 100纳秒)
    out_micro = (int)((unix100ns / 10ULL) % 1000000ULL);
    
    return unixSec;
#else
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    out_micro = ts.tv_nsec / 1000;
    return (uint64)ts.tv_sec;
#endif
}

// --- 以下是你原有的高精度单调时间逻辑 (秒表用) ---
uint64 getHighResTimestamp() {
#ifdef _WIN32
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return (uint64)count.QuadPart;
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64)ts.tv_sec * 1000000000ULL + ts.tv_nsec;
#endif
}

double getElapsedMicroseconds(uint64 start, uint64 end) {
#ifdef _WIN32
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    return (double)(end - start) * 1000000.0 / freq.QuadPart;
#else
    return (double)(end - start) / 1000.0;
#endif
}