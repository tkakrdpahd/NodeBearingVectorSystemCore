/* SocketServer.cpp
 * Security: Confidential
 * Author: Minseok Doo
 * Date: Oct 20, 2024
 * 
 * Purpose of Class
 * Open & Manage Socket Server
 */

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <thread>

#include "SocketServer.h"

SocketServer::SocketServer(int serverPort)
    : serverPort(serverPort), serverSocketFd(-1) {
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(serverPort);
}

SocketServer::~SocketServer() {
    closeServer();
}

bool SocketServer::startServer() {
    serverSocketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocketFd < 0) {
        std::cerr << "Failed to create socket." << std::endl;
        return false;
    }

    if (bind(serverSocketFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Bind failed." << std::endl;
        return false;
    }

    if (listen(serverSocketFd, 3) < 0) {
        std::cerr << "Listen failed." << std::endl;
        return false;
    }

    std::cout << "Server started and listening on port " << serverPort << std::endl;
    return true;
}

void SocketServer::closeServer() {
    if (serverSocketFd >= 0) {
        close(serverSocketFd);
        serverSocketFd = -1;
        std::cout << "Server closed." << std::endl;
    }
}
