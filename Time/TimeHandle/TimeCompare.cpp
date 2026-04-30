#include "../HeaderFiles/HandleInterface.h"
#include "../HeaderFiles/GitInterface.h"
#include "../HeaderFiles/Defines.h"

#define TIME_DIFF_LIMIT 60

// 原子职责：仅执行逻辑判定[cite: 3]
int checkTimeAccuracy() {
    uint64 sysS, netS;
    int sysM;
    
    // 从供应层获取原始数据[cite: 3, 7]
    getFullTimeData(sysS, sysM, netS);
    
    // 网络获取失败判定为不可信[cite: 3, 6]
    if (netS == 0) return 0; 
    
    // 使用 long long 显式转换，防止 uint64 减法回绕溢出[cite: 3]
    long long diff = (long long)netS - (long long)sysS;
    if (diff < 0) diff = -diff;
    
    // 使用 Defines.h 中的原子常量 (60秒)[cite: 3]
    return (diff <= TIME_DIFF_LIMIT) ? 1 : 0;
}