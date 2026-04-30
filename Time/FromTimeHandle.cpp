#include "GitInterface.h"
#include "HandleInterface.h"
#include "TimeBridge.h"
#include "Defines.h"

// 增加一个辅助函数，让 API 知道目前是否有过成功同步
static bool g_hasSynced = false;
extern "C" bool isTimeSynced() { return g_hasSynced; }

FullTime getValidatedFullTime() {
    static uint64 lastCheckSec = 0;
    static uint64 lastAttemptSec = 0;
    static long long timeOffset = 0;
    
    int sysM;
    uint64 sysS = getSystemRawSeconds(sysM);

    if (lastCheckSec == 0 || (sysS - lastCheckSec >= 3600)) {
        if (lastAttemptSec == 0 || (sysS - lastAttemptSec >= 300)) {
            lastAttemptSec = sysS;
            uint64 netS = getNetworkRawSeconds();
            
            if (netS != 0) {
                lastCheckSec = sysS;
                timeOffset = (long long)netS - (long long)sysS;
                g_hasSynced = true; // 同步成功标记
            }
        }
    }
    
    // 计算目标时间：有偏移加偏移，没偏移则 timeOffset 为 0，即本地时间
    uint64 targetSec = (uint64)((long long)sysS + timeOffset);
    return convertToFull(targetSec, sysM);
}