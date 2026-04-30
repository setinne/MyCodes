#include "Common.h"
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

uint64 getNetworkRawSeconds() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) return 0;

    // 分布在全球各地的顶级授时中心 IP
    const char* ntpServers[] = {
        // --- 中国 (极速响应) ---
        "114.118.7.163",   // 中国国家授时中心 (西安)
        "203.107.6.88",    // 阿里云 (杭州/北京)
        "106.55.184.199",  // 腾讯云 (深圳/上海)
        
        // --- 亚太地区 ---
        "203.206.205.83",  // 澳大利亚政府授时中心 (堪培拉)
        "210.173.160.27",  // 日本福冈大学 (亚洲最早的授时源之一)
        "118.189.138.5",   // 新加坡国立大学 (新加坡)

        // --- 欧洲地区 ---
        "162.159.200.1",   // Cloudflare (全球/欧洲节点)
        "194.58.203.20",   // 瑞典国家授时中心 (Netnod)
        "131.188.3.220",   // 德国埃朗根-纽伦堡大学 (中欧经典节点)

        // --- 美洲地区 ---
        "129.6.15.28",     // 美国国家标准技术研究院 (NIST - 科罗拉多州)
        "216.239.35.0",    // Google Time (美国/全球)
        "17.253.14.125"    // Apple Time (库比蒂诺/全球)
    };
    int serverCount = sizeof(ntpServers) / sizeof(ntpServers[0]);

    uint64 result = 0;

    for (int i = 0; i < serverCount; ++i) {
        SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (sock == INVALID_SOCKET) continue;

        // 设置更短的超时，以便在故障时快速切换
        // XP 下单位是毫秒。1000ms 对国内够了，对跨国节点略显紧迫，设为 1200ms 比较平衡
        int timeout = 1200; 
        setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));

        sockaddr_in server;
        server.sin_family = AF_INET;
        server.sin_port = htons(123);
        server.sin_addr.s_addr = inet_addr(ntpServers[i]);

        unsigned char msg[48] = {0x1B, 0};

        if (sendto(sock, (char*)msg, sizeof(msg), 0, (sockaddr*)&server, sizeof(server)) != SOCKET_ERROR) {
            if (recv(sock, (char*)msg, sizeof(msg), 0) > 0) {
                unsigned int high = (msg[40] << 24) | (msg[41] << 16) | (msg[42] << 8) | msg[43];
                result = (uint64)high - 2208988800ULL;
                closesocket(sock);
                break; // 只要有一个返回，就退出循环
            }
        }
        closesocket(sock);
    }

    WSACleanup();
    return result;
}