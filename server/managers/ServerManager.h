/**
 * serverManager.h
 * Linked File: serverManager.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 13, 2024
 * Last Modified: Nov 13, 2024
 * 
 * Purpose: Manage ServerManager, handling both socket communication and events.
 */

#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include <sys/socket.h>  // For socket functions: recv, send
#include <unistd.h>      // For close function
#include <iostream>      // For standard I/O
#include <cstring>       // For strerror
#include <atomic>

#include "ServerManager.h"
#include "SocketManager.h"
#include "EventManager.h"

class ServerManager {
    private:
        std::atomic<bool> isRunning; // 서버 실행 상태를 나타내는 원자 변수
        SocketManager socketManager;  // Manages socket connections
        EventManager eventManager;    // Manages event handling

        void handleClient(int clientSocket);  // Private method to handle client requests
    public:
        ServerManager();
        ~ServerManager();

        void start();  // Starts the server and listens for client requests
        void stop();
};

#endif // SERVERMANAGER_H
