#ifndef GIT_INTERFACE_H
#define GIT_INTERFACE_H

#include "Defines.h" // 必须包含这个，否则底层函数不认识 uint64[cite: 1]

uint64 getSystemRawSeconds(int& out_micro);
uint64 getNetworkRawSeconds();
uint64 getHighResTimestamp();
void getFullTimeData(uint64& sysSec, int& sysMicro, uint64& netSec);

#endif