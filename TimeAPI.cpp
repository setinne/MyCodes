#include "TimeBridge.h"

// API 接口：获取人类可读的时间字符串
const char* api_GetFormattedTime() {
    FullTime ft = getValidatedFullTime();
    // 简单的格式化拼接逻辑...
}
