#ifndef HANDLE_INTERFACE_H
#define HANDLE_INTERFACE_H

#include "Defines.h"

// 结构化时间原子[cite: 1]
struct FullTime {
    int year, month, day;
    int hour, minute, second;
    int ms, us;
};

// 比较原子接口：误差超过一分钟返回 0
int checkTimeAccuracy(); 

// 格式化原子接口
FullTime convertToFull(uint64 sec, int micro);

#endif