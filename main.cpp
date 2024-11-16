/**
 * main.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 13, 2024
 * Last Modified: Nov 13, 2024
 */

#include <memory>
#include <thread>
#include "DrawWindow.h"
#include "ServerManager.h"

int main(int argc, char** argv) {
    ServerManager serverManager;

    // 서버를 별도 스레드에서 실행
    std::thread serverThread([&serverManager]() {
        serverManager.start();
    });

    // 인터페이스 실행
    interface(argc, argv);

    // 인터페이스 종료 후 서버 정리
    serverManager.stop();
    if (serverThread.joinable()) {
        serverThread.join();
    }

    return 0;
}
