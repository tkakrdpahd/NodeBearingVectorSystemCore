/**
 * serverManager.cpp
 * Implements ServerManager to manage socket and event handling.
 * Author: Minseok Doo
 * Date: Oct 13, 2024
 * Last Modified: Nov 13, 2024
 */

#include "ServerManager.h"
#include <iostream>
#include <sstream>
#include <unistd.h>

ServerManager::ServerManager() {
    // Initialization: Server will be started by SocketManager's constructor
    std::cout << "ServerManager initialized on port " << socketManager.getPort() << std::endl;
}

ServerManager::~ServerManager() {
    socketManager.closeServer();  // Ensure the server socket is closed on destruction
}

void ServerManager::start() {
    isRunning = true; // 서버 실행 시작

    std::cout << "ServerManager starting and waiting for clients on port " << socketManager.getPort() << "..." << std::endl;

    while (isRunning) { // 플래그 기반으로 실행 제어
        int clientSocket = socketManager.acceptClient();
        if (clientSocket < 0) {
            if (!isRunning) break; // 종료 중이면 루프 탈출
            std::cerr << "Failed to accept client connection." << std::endl;
            continue;
        }

        // Handle the client request
        handleClient(clientSocket);

        // Close the client socket after handling the request
        close(clientSocket);
    }

    std::cout << "ServerManager stopped." << std::endl;
}

void ServerManager::stop() {
    isRunning = false; // 실행 상태 종료
    socketManager.closeServer(); // 소켓 닫기
}

void ServerManager::handleClient(int clientSocket) {
    char buffer[1024] = {0};
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);

    if (bytesReceived < 0) {
        std::cerr << "Failed to receive data from client." << std::endl;
        return;
    }

    // Basic HTTP-like request parsing
    std::istringstream requestStream(buffer);
    std::string method, path, data;

    requestStream >> method >> path;
    std::getline(requestStream, data);  // Remainder of data after method and path

    // Pass request to EventManager for processing
    if (path == "/api") {
        eventManager.processRequest(method, data);
    } else {
        std::cerr << "Invalid API path: " << path << std::endl;
    }

    // Send a response back to the client
    std::string response = "HTTP/1.1 200 OK\nContent-Type: text/plain\n\nRequest processed by ServerManager.";
    send(clientSocket, response.c_str(), response.length(), 0);
}
