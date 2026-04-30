#include "Common.h"

// 将底层的两个函数整合在一起，方便上层一键获取
void getFullTimeData(uint64& sysSec, int& sysMicro, uint64& netSec) {
    sysSec = getSystemRawSeconds(sysMicro); // 对应 LocalTime.cpp
    netSec = getNetworkRawSeconds();        // 对应 NetTime.cpp
}