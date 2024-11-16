/**
 * main.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 13, 2024
 * Last Modified: Nov 13, 2024
 */

#include <memory>
#include "DrawWindow.h"
#include "SocketManager.h"

// 전역 스마트 포인터 선언
std::shared_ptr<SocketManager> g_socketManager;

int main(int argc, char** argv) {
    // SocketManager 초기화
    g_socketManager = std::make_shared<SocketManager>();

    // 인터페이스 실행
    interface(argc, argv);

    return 0;
}