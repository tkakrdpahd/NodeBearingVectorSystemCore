/**
 * SocketManager.h
 * Author: Minseok Doo
 * Date: 2024-11-26
 * Description: SocketManager class for handling socket connections
 */
#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H

#include <iostream>
#include <memory>
#include <cstdint>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <drogon/drogon.h>

#include <gtest/gtest.h>

class SocketManager {
    private:
        // Port number for the socket connection
        uint16_t _port;
        // Flag indicating if socket is currently running
        bool _isRunning;

        // Find an available port to use
        void FindPort() {
            _port = 8080;
            int sock;
            struct sockaddr_in addr;
            
            while (_port < 65535) {  // Maximum port number
                sock = socket(AF_INET, SOCK_STREAM, 0);
                if (sock < 0) {
                    std::cerr << "Failed to create socket" << std::endl;
                    return;
                }

                addr.sin_family = AF_INET;
                addr.sin_addr.s_addr = INADDR_ANY;
                addr.sin_port = htons(_port);

                if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) == 0) {
                    // Successfully bound to port
                    close(sock);
                    return;
                }

                close(sock);
                _port++;
            }

            // If we get here, no ports were available
            std::cerr << "No available ports found" << std::endl;
            _port = 0;
        }

        FRIEND_TEST(SocketManagerTest, FindPort);
    public:
        // Start the socket server on specified port
        void Run(uint16_t port) {
            _port = port;
            drogon::app().addListener("0.0.0.0", _port);
            drogon::app().run();
        }
        // Stop the socket server
        void Stop() {
            drogon::app().quit();
        }
        // Get the current port number
        uint16_t GetPort() { return _port; }

        // Constructor - initializes with default port 8080
        SocketManager() : _port(8080), _isRunning(false) {}
        // Default destructor
        ~SocketManager() = default;
};

#endif // SOCKETMANAGER_H
