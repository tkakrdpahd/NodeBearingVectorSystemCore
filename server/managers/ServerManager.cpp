/**
 * serverManager.cpp
 * Implements ServerManager to manage socket and event handling.
 * Author: Minseok Doo
 * Date: Oct 13, 2024
 * Last Modified: Nov 13, 2024
 */
#include "ServerManager.h"

ServerManager::ServerManager() : isRunning(false), _socketManager(isRunning) {
    std::cout << "ServerManager initialized on port " << _socketManager.getPort() << std::endl;
}

ServerManager::~ServerManager() {
    stop();
}

void ServerManager::start() {
    if (isRunning.load()) {
        std::cerr << "Server is already running." << std::endl;
        return;
    }

    if (!_socketManager.StartServer()) {
        std::cerr << "Failed to start the server. Exiting start method." << std::endl;
        return;
    }

    isRunning.store(true);
    std::cout << "ServerManager starting on port " << _socketManager.getPort() << std::endl;

    _socketManager.ListenForClients();
}

void ServerManager::stop() {
    if (!isRunning.load()) {
        std::cerr << "Server is not running." << std::endl;
        return;
    }

    isRunning.store(false);
    _socketManager.closeServer();
    std::cout << "ServerManager stopped." << std::endl;
}
