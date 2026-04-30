#ifndef GIT_INTERFACE_H
#define GIT_INTERFACE_H

#include "Defines.h"

// 供应层原子接口
uint64 getSystemRawSeconds(int& out_micro);
uint64 getNetworkRawSeconds();
uint64 getHighResTimestamp();

// 汇总供应接口[cite: 1]
void getFullTimeData(uint64& sysSec, int& sysMicro, uint64& netSec);

#endif