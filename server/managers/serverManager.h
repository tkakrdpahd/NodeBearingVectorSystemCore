/**
 * serverManager.h
 * Linked File: serverManager.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 13, 2024
 * Last Modified: Nov 13, 2024
 * 
 * Purpose: Manage ServerManagers
 */

#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include "SocketManager.h"
#include "EventManager.h"

class ServerManager {
    private:
        /* data */
    public:
        ServerManager(/* args */);
        ~ServerManager();
};

ServerManager::ServerManager(/* args */) {
}

ServerManager::~ServerManager() {
}


#endif // SERVERMANAGER_H