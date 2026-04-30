#ifndef TIME_BRIDGE_H
#define TIME_BRIDGE_H

#include "HandleInterface.h"

// 来自 FromTimeGit.cpp：仅同步数据，不处理格式
void syncSystemWithNetwork();

// 来自 FromTimeHandle.cpp：获取最终可信的结构化时间
FullTime getValidatedFullTime();

#endif