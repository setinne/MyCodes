#include "../HeaderFiles/HandleInterface.h"
#include <time.h>

// 原子化职责：将原始秒和微秒处理成结构化格式
FullTime convertToFull(uint64 seconds, int microseconds) {
    FullTime ft = {0};

    time_t rawTime = (time_t)seconds;

    // 跨平台处理：WinXP/Win11 使用 localtime，Linux 建议用 localtime_r
#ifdef _WIN32
    struct tm* timeInfo = localtime(&rawTime);
#else
    struct tm result;
    struct tm* timeInfo = localtime_r(&rawTime, &result);
#endif

    if (timeInfo) {
        ft.year = timeInfo->tm_year + 1900;
        ft.month = timeInfo->tm_mon + 1;
        ft.day = timeInfo->tm_mday;
        ft.hour = timeInfo->tm_hour;
        ft.minute = timeInfo->tm_min;
        ft.second = timeInfo->tm_sec;
    }

    // 对应 HeaderFiles/HandleInterface.h 中的结构体成员名
    ft.us = microseconds;
    ft.ms = microseconds / 1000;

    return ft;
}