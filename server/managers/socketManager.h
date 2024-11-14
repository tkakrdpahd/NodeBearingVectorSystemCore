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

#include <string>
#include <netinet/in.h>

class SocketManager {
private:
    int serverSocket;
    int port;
    struct sockaddr_in serverAddress;

    int FindPortNumber();

public:
    SocketManager();
    ~SocketManager();

    bool StartServer();
    void ListenForClients();
    void sendResponse(int clientSocket, const std::string& message);
    void closeServer();

    int getPort() const;          // New member function to get the port number
    int acceptClient();           // New member function to accept client connections
};

#endif // SOCKETMANAGER_H
