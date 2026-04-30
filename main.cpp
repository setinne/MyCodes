#include <iostream>
#include <windows.h>

// 必须使用 extern "C" 匹配 API 的定义方式[cite: 9]
extern "C" const char* api_GetFormattedTime();

int main() {
    std::cout << "--- Time Engine Test ---" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << "Result: " << api_GetFormattedTime() << std::endl;
        Sleep(1000);
    }
    return 0;
}