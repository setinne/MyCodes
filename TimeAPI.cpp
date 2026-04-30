#include "TimeBridge.h"
#include <stdio.h>

extern "C" bool isTimeSynced();

extern "C" {
    const char* api_GetFormattedTime() {
        static char buf[64];
        static bool netErrorShowed = false; // 控制错误提示次数
        
        FullTime ft = getValidatedFullTime();
        
        // 如果从未同步成功过，且还没报过错，则优先返回 NetError
        if (!isTimeSynced() && !netErrorShowed) {
            netErrorShowed = true; 
            return "NetError";
        }
        
        // 之后的调用（或已同步成功的情况）全部返回格式化时间
        sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d.%03d", 
                ft.year, ft.month, ft.day, ft.hour, ft.minute, ft.second, ft.ms);
                
        return buf;
    }
}