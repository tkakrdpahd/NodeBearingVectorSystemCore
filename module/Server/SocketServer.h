/**
 * SocketServer.h
 * Linked file SocketServer.cpp
 * Security: Confidential
 * Author: Minseok Doo
 * Date: Oct 20, 2024
 * Last Modified: Nov 11, 2024
 * 
 * Purpose of Class
 * Open & Manage Socket Server
 */

#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include <string>
#include <arpa/inet.h>

class SocketServer {
public:
    SocketServer(int serverPort);
    ~SocketServer();

    bool startServer();
    void closeServer();

private:
    int serverPort;
    int serverSocketFd;
    struct sockaddr_in serverAddr;
};

#endif // SOCKETSERVER_H
