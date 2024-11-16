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

#include "SocketManager.h"
#include "EventManager.h"

class ServerManager {
    private:
        std::atomic<bool> isRunning;
        SocketManager _socketManager;
        EventManager _eventManager;

        // Private method to handle client requests
        void handleClient(int clientSocket);
    public:
        ServerManager();
        ~ServerManager();

        void start();
        void stop();
};

#endif // SERVERMANAGER_H
