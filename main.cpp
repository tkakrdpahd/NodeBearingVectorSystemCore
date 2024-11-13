/**
 * main.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 13, 2024
 * Last Modified: Nov 13, 2024
 */

#include <iostream>

#include "Vector3.h"
#include "NodeVector.h"

int main() {
    // Create SceneManager instance; std::shared_ptr
        // Load operators modules
    // Create ObjectManager instance refer to SceneManager instance
        // Load entities modules
        // Load vectors modules
        // Load segments modules
    // Create ServerManager instnace refer to SceneManager instance
        // ServerManager load SocketManager and EventManager
            // SocketManager load Socket Server and return Socket Number
            // EventManager load API
        // ServerManager instance return listenForClients();
    // Call interfaces
        // Call menu
        // Call simulator
    
    std::cout << "Hello, World!!!" << std::endl;

    Vector3 vector;
    NodeVector nodeVector;

    std::cout << vector << std::endl;
    std::cout << nodeVector << std::endl;

    return 0;
}
