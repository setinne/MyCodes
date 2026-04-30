#ifndef COMMON_H
#define COMMON_H

#include <string>

typedef unsigned __int64 uint64;

// 定义原子化时间结构体
struct TimeComponents {
    int year, month, day;
    int hour, minute, second;
    int millisecond, microsecond;
};

// 声明底层获取函数
uint64 getSystemRawSeconds(int& out_micro);
uint64 getNetworkRawSeconds();
uint64 getHighResTimestamp();

// 声明 Handle 层的处理函数
TimeComponents breakDownTime(uint64 seconds, int microseconds);

#endif