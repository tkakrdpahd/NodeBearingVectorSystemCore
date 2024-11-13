
#include "socketManager.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <stdexcept>

// 기본 생성자
SocketManager::SocketManager() {
    serverSocket = -1;
    port = FindPortNumber();  // 포트 번호 설정

    // 서버 자동 시작
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

    // 소켓 바인딩
    if (bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Binding failed. Error: " << strerror(errno) << std::endl;
        return false;
    }

    // 서버 대기 설정
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

    // 클라이언트와 메시지 주고받기
    char buffer[1024] = {0};
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived < 0) {
        std::cerr << "Error in recv(). Error: " << strerror(errno) << std::endl;
    } else {
        std::cout << "Received message from client: " << buffer << std::endl;
    }

    // 클라이언트에 응답
    sendResponse(clientSocket, "Hello from server!");
    
    // 클라이언트 소켓 닫기
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

// 포트 번호 찾기 (기본값으로 8080 사용)
int SocketManager::FindPortNumber() {
    return 8080;  // 기본적으로 8080 포트 사용
}
