/**
 * SocketManager.cpp
 * Purpose: Manage Socket Server
 * 
 */
#include "SocketManager.h"
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

SocketManager::SocketManager(std::atomic<bool>& runningFlag)
    : serverSocket(-1), port(0), isRunning(runningFlag) {
    port = findPortNumber();
}

SocketManager::~SocketManager() {
    closeServer();
}

bool SocketManager::StartServer() {
    if (isRunning.load()) {
        std::cerr << "Server is already running on port " << port << "." << std::endl;
        return false;
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Failed to create socket. Error: " << strerror(errno) << std::endl;
        return false;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    if (bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Binding failed. Error: " << strerror(errno) << std::endl;
        return false;
    }

    if (listen(serverSocket, 5) < 0) {
        std::cerr << "Error while trying to listen. Error: " << strerror(errno) << std::endl;
        return false;
    }

    isRunning.store(true);
    std::cout << "Server started on port " << port << std::endl;
    return true;
}

void SocketManager::ListenForClients() {
    std::cout << "Waiting for incoming client connections..." << std::endl;

    while (isRunning.load()) {
        int clientSocket = acceptClient();
        if (clientSocket < 0) {
            if (!isRunning.load()) {
                break; // 서버가 종료된 상태면 루프 종료
            }
            std::cerr << "Failed to accept connection. Error: " << strerror(errno) << std::endl;
            continue;
        }

        std::cout << "Client connected." << std::endl;
        sendResponse(clientSocket, "Hello from server!");
        close(clientSocket);
    }
}

void SocketManager::sendResponse(int clientSocket, const std::string& message) {
    if (send(clientSocket, message.c_str(), message.size(), 0) < 0) {
        std::cerr << "Failed to send response. Error: " << strerror(errno) << std::endl;
    }
}

void SocketManager::closeServer() {
    if (serverSocket != -1) {
        close(serverSocket);
        serverSocket = -1;
        isRunning.store(false);
        std::cout << "Server socket closed." << std::endl;
    }
}

int SocketManager::findPortNumber() {
    int startPort = 8080;
    int testSocket;
    sockaddr_in testAddress;
    testAddress.sin_family = AF_INET;
    testAddress.sin_addr.s_addr = INADDR_ANY;

    while (true) {
        testSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (testSocket == -1) {
            throw std::runtime_error("Failed to create socket for port testing.");
        }

        testAddress.sin_port = htons(startPort);

        if (bind(testSocket, (sockaddr*)&testAddress, sizeof(testAddress)) == 0) {
            close(testSocket);
            break;
        }

        close(testSocket);
        startPort++;
    }

    return startPort;
}

int SocketManager::getPort() const {
    return port;
}

int SocketManager::acceptClient() {
    sockaddr_in clientAddress;
    socklen_t clientSize = sizeof(clientAddress);

    int clientSocket = accept(serverSocket, (sockaddr*)&clientAddress, &clientSize);
    if (clientSocket < 0 && isRunning.load()) {
        std::cerr << "Error accepting client connection. Error: " << strerror(errno) << std::endl;
    }
    return clientSocket;
}
