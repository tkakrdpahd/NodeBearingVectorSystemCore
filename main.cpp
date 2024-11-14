/**
 * main.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 13, 2024
 * Last Modified: Nov 13, 2024
 */

#include <iostream>
#include <thread>

#include "ObjectManager.h"
#include "ServerManager.h"

int main() {
    
    std::cout << "Hello, World!!!" << std::endl;

    // Create SceneManager instance; std::shared_ptr
        // Load operators modules
    // Create ObjectManager instance refer to SceneManager instance
    ObjectManager obj1;

    // Create a NodeVector
    auto node = obj1.CreateNodeVector(1, Vector3(1.0f, 2.0f, 3.0f));
    
    // Automatically find the NodeVector by index and create a BearingVector
    auto bearing = obj1.CreateBearingVector(1, Vector3(5.0f, 5.0f, 5.0f), Vector3(0.5f, 0.8f, 1.2f));

    if (node) {
        std::cout << *node << std::endl;
    }
    if (bearing) {
        std::cout << *bearing << std::endl;
    }
    
    // Create ServerManager instnace refer to SceneManager instance
    try {
        ServerManager serverManager; // ServerManager 인스턴스 생성

        std::thread serverThread([&serverManager]() { // 서버 시작 및 클라이언트 요청을 비동기적으로 처리
            serverManager.start(); // 클라이언트 연결 대기 및 처리 시작
        });

        std::cout << "서버가 성공적으로 시작되었습니다." << std::endl;
        
        serverThread.join(); // 서버 스레드가 종료될 때까지 대기
        
    } catch (const std::exception& e) {
        std::cerr << "서버 시작 중 오류 발생: " << e.what() << std::endl;
    }
    // Call interfaces
        // Call menu
        // Call simulator

    return 0;
}
