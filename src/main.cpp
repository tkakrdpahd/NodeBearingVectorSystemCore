// main.cpp
#include <iostream>
#include "Server.h"

int main() {
    std::cout << "Hello, World!!!" << std::endl;

    Server server;
    server.run();
    return 0;
}