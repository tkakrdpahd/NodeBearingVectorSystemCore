/**
 * main.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 13, 2024
 * Last Modified: Nov 11, 2024
 */

#include <iostream>
#include <cmath>
#include "CoordinateConverter.h"
#include "Vector3.h"
#include "NodeVector.h"
#include "BearingVector.h"
#include "SocketServer.h"

// Socket 서버 테스트 함수로 AttributesManager의 데이터를 반환하게 함
void SocketServerTest() {
    int serverPort = 8080;
    SocketServer server(serverPort);

    if (server.startServer()) {
        std::cerr << "Server start." << std::endl;
    } else {
        std::cerr << "Failed to start the server." << std::endl;
    }
}

int main() {
    SocketServerTest();
    return 0;
}
