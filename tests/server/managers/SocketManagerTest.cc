/**
 * SocketManagerTest.cc 
 * Author: Minseok Doo
 * Date: 2024-11-26
 */

#include "SocketManager.h"
#include <gtest/gtest.h>
#include <thread>
#include <chrono>

TEST(SocketManagerTest, FindPort) {
    SocketManager socketManager;
    
    // Start server in separate thread
    std::thread serverThread([&socketManager]() {
        socketManager.Run(8080);
    });

    // Give some time for server to start
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Force stop
    socketManager.Stop();
    
    // Wait for thread to finish
    if (serverThread.joinable()) {
        serverThread.join();
    }

    socketManager.FindPort();
    EXPECT_GT(socketManager.GetPort(), 0);
}
