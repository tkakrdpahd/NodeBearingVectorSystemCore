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
#include "SocketManager.h"

int main() {
    // Create SceneManager instance; std::shared_ptr
        // Load operators modules
    // Create ObjectManager instance refer to SceneManager instance
        // Load entities modules
        // Load vectors modules
        // Load segments modules
    // Create ServerManager instnace refer to SceneManager instance
        // ServerManager load SocketManager and EventManager
            // SocketManager load Socket Server and return Socket Number
            // EventManager load API
        // ServerManager instance return listenForClients();
    // Call interfaces
        // Call menu
        // Call simulator
    
    std::cout << "Hello, World!!!" << std::endl;

    SocketManager server;

    // 멤버 함수 ListenForClients를 람다로 감싸서 실행
    std::thread serverThread([&server]() {
        server.ListenForClients();
    });

    serverThread.join(); // 메인 쓰레드에서 서버 쓰레드 대기

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

    return 0;
}
