#include "TimeGit/Common.h"
#include <string>

// --- 原子接口 1：高精度同步校准 ---
// 综合系统与网络时间，返回一个经过校准的微秒级 Unix 时间戳
uint64 getCalibratedTimestamp() {
    uint64 sysSec, netSec;
    int sysMicro;
    getFullTimeData(sysSec, sysMicro, netSec);
    
    // 如果网络时间获取成功，以网络时间为准进行毫秒级修偏
    if (netSec != 0) {
        return (netSec * 1000000ULL) + (sysMicro % 1000000ULL);
    }
    // 否则退而求其次使用系统时间
    return (sysSec * 1000000ULL) + sysMicro;
}

// --- 原子接口 2：业务级的秒表控制 ---
// 隐藏 QPC 频率转换的复杂性，直接给上层返回“经过了多少毫秒”
double getStopwatchElapsedMS(uint64 startCount) {
    uint64 currentCount = getHighResTimestamp();
    // 调用底层 Common.h 声明的转换函数
    extern double getElapsedMicroseconds(uint64 start, uint64 end);
    return getElapsedMicroseconds(startCount, currentCount) / 1000.0;
}

// --- 原子接口 3：标准日志前缀 ---
// 生成如 "[17:30:05.123]" 这种原子化的格式化字符串
std::string getLogPrefix() {
    int micro;
    uint64 sec = getSystemRawSeconds(micro);
    // 这里可以调用你 Time.cpp 里的转换逻辑
    return "格式化后的时间"; 
}