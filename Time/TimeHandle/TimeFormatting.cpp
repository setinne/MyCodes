#include "Common.h"
#include <time.h>

// 原子化职责：将原始秒和微秒处理成结构化格式
TimeComponents breakDownTime(uint64 seconds, int microseconds) {
    TimeComponents tc;
    
    // 转换为 C 标准库的 time_t
    time_t rawTime = (time_t)seconds;
    struct tm* timeInfo = localtime(&rawTime);

    // 填充年月日时分秒
    tc.year = timeInfo->tm_year + 1900;
    tc.month = timeInfo->tm_mon + 1;
    tc.day = timeInfo->tm_mday;
    tc.hour = timeInfo->tm_hour;
    tc.minute = timeInfo->tm_min;
    tc.second = timeInfo->tm_sec;

    // 处理微秒和毫秒
    tc.microsecond = microseconds;
    tc.millisecond = microseconds / 1000;

    return tc;
}