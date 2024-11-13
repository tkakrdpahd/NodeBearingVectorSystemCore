/**
 * socketManager.h
 * Linked File: socketManager.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 13, 2024
 * Last Modified: Nov 13, 2024
 * 
 * Purpose: Manage Socket Server
 */

#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H

#include <iostream>
#include <string>
#include <netinet/in.h>

class SocketManager {
private:
    int serverSocket;                  // 서버 소켓 파일 디스크립터
    sockaddr_in serverAddress;         // 서버 주소 정보
    int port;                          // 서버 포트 번호

    int FindPortNumber();              // 포트 번호 찾기 함수
    bool StartServer();                // 서버 시작 함수

public:
    SocketManager();
    ~SocketManager();

    void ListenForClients();
    void sendResponse(int clientSocket, const std::string& message);
    void closeServer();
};

#endif // SOCKETMANAGER_H
