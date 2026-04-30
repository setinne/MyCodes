#include "HandleInterface.h"
#include "GitInterface.h"

// 原子职责：仅执行逻辑判定
int checkTimeAccuracy() {
    uint64 sysS, netS;
    int sysM;
    
    // 从供应层拿原始数据
    getFullTimeData(sysS, sysM, netS);
    
    if (netS == 0) return 0; // 网络获取失败判定为不可信
    
    // 计算绝对差值
    long long diff = (long long)netS - (long long)sysS;
    if (diff < 0) diff = -diff;
    
    return (diff <= TIME_DIFF_LIMIT) ? 1 : 0;
}
