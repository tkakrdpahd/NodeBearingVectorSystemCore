/**
 * SocketManager.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 13, 2024
 * Last Modified: Nov 14, 2024
 * 
 * Purpose: Manage Socket Server
 */

#include "SocketManager.h"
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

SocketManager::SocketManager() {
    serverSocket = -1;
    port = FindPortNumber();

    if (!StartServer()) {
        throw std::runtime_error("Failed to start the server. Please check configurations or port availability.");
    }
}

SocketManager::~SocketManager() {
    closeServer();
}

bool SocketManager::StartServer() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Failed to create socket." << std::endl;
        return false;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    if (bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Binding failed. Error: " << strerror(errno) << std::endl;
        return false;
    }

    if (listen(serverSocket, 3) < 0) {
        std::cerr << "Error while trying to listen. Error: " << strerror(errno) << std::endl;
        return false;
    }

    std::cout << "Server started on port " << port << std::endl;
    return true;
}

void SocketManager::ListenForClients() {
    sockaddr_in clientAddress;
    socklen_t clientSize = sizeof(clientAddress);

    std::cout << "Waiting for incoming client connections..." << std::endl;
    int clientSocket = accept(serverSocket, (sockaddr*)&clientAddress, &clientSize);
    if (clientSocket < 0) {
        std::cerr << "Failed to accept connection. Error: " << strerror(errno) << std::endl;
        return;
    }

    // Handle client connection
    char buffer[1024] = {0};
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived < 0) {
        std::cerr << "Error in recv(). Error: " << strerror(errno) << std::endl;
    } else {
        std::cout << "Received message from client: " << buffer << std::endl;
    }

    sendResponse(clientSocket, "Hello from server!");
    close(clientSocket);
}

void SocketManager::sendResponse(int clientSocket, const std::string& message) {
    send(clientSocket, message.c_str(), message.size(), 0);
}

void SocketManager::closeServer() {
    if (serverSocket != -1) {
        close(serverSocket);
        serverSocket = -1;
        std::cout << "Server socket closed." << std::endl;
    }
}

int SocketManager::FindPortNumber() {
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

// New function: Get the current port number
int SocketManager::getPort() const {
    return port;
}

// New function: Accept a client connection
int SocketManager::acceptClient() {
    sockaddr_in clientAddress;
    socklen_t clientSize = sizeof(clientAddress);
    return accept(serverSocket, (sockaddr*)&clientAddress, &clientSize);
}
