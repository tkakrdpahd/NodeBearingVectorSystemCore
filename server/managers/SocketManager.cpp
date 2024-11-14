#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <stdexcept>
#include <iostream>

#include "SocketManager.h"

// 기본 생성자
SocketManager::SocketManager() {
    serverSocket = -1;
    port = FindPortNumber();  // Find an available port

    // Start the server automatically
    if (!StartServer()) {
        throw std::runtime_error("Failed to start the server. Please check configurations or port availability.");
    }
}

// 소멸자
SocketManager::~SocketManager() {
    closeServer();
}

// 서버 시작 메소드
bool SocketManager::StartServer() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Failed to create socket." << std::endl;
        return false;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    // Attempt to bind the socket
    if (bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Binding failed. Error: " << strerror(errno) << std::endl;
        return false;
    }

    // Start listening for incoming connections
    if (listen(serverSocket, 3) < 0) {
        std::cerr << "Error while trying to listen. Error: " << strerror(errno) << std::endl;
        return false;
    }

    std::cout << "Server started on port " << port << std::endl;
    return true;
}

// 클라이언트를 기다리고 응답을 받는 메소드
void SocketManager::ListenForClients() {
    sockaddr_in clientAddress;
    socklen_t clientSize = sizeof(clientAddress);

    std::cout << "Waiting for incoming client connections..." << std::endl;
    int clientSocket = accept(serverSocket, (sockaddr*)&clientAddress, &clientSize);
    if (clientSocket < 0) {
        std::cerr << "Failed to accept connection. Error: " << strerror(errno) << std::endl;
        return;
    }

    char host[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &clientAddress.sin_addr, host, INET_ADDRSTRLEN);
    std::cout << "Connection accepted from " << host << ":" << ntohs(clientAddress.sin_port) << std::endl;

    // Receive message from the client
    char buffer[1024] = {0};
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived < 0) {
        std::cerr << "Error in recv(). Error: " << strerror(errno) << std::endl;
    } else {
        std::cout << "Received message from client: " << buffer << std::endl;
    }

    // Send response to the client
    sendResponse(clientSocket, "Hello from server!");
    
    // Close the client socket
    close(clientSocket);
}

// 클라이언트에 응답을 보내는 메소드
void SocketManager::sendResponse(int clientSocket, const std::string& message) {
    send(clientSocket, message.c_str(), message.size(), 0);
}

// 서버 종료 메소드
void SocketManager::closeServer() {
    if (serverSocket != -1) {
        close(serverSocket);
        serverSocket = -1;
        std::cout << "Server socket closed." << std::endl;
    }
}

// Find an available port, starting at 8080 and incrementing if the port is in use
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

        // Try binding to the current port
        if (bind(testSocket, (sockaddr*)&testAddress, sizeof(testAddress)) == 0) {
            close(testSocket);  // Close test socket as port is free
            break;              // Found an available port
        }

        // If binding fails, increment port and try again
        close(testSocket);
        startPort++;
    }

    return startPort;  // Return the available port number
}
