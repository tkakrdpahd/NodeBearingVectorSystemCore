/**
 * eventManager.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 13, 2024
 * Last Modified: Nov 13, 2024
 */

#include "EventManager.h"

EventManager::EventManager() {
    // Initialization code if needed
}

EventManager::~EventManager() {
    // Cleanup code if needed
}

// GET 요청 처리
std::string EventManager::handleGetRequest(const std::string& data) {
    std::cout << "Handling GET request with data: " << data << std::endl;
    return "GET request handled";
}

// POST 요청 처리
std::string EventManager::handlePostRequest(const std::string& data) {
    std::cout << "Handling POST request with data: " << data << std::endl;
    return "POST request handled";
}

// PUT 요청 처리
std::string EventManager::handlePutRequest(const std::string& data) {
    std::cout << "Handling PUT request with data: " << data << std::endl;
    return "PUT request handled";
}

// DELETE 요청 처리
std::string EventManager::handleDeleteRequest(const std::string& data) {
    std::cout << "Handling DELETE request with data: " << data << std::endl;
    return "DELETE request handled";
}

std::string EventManager::processRequest(const std::string& method, const std::string& data) {
    if (method == "GET") {
        return handleGetRequest(data);
    } else if (method == "POST") {
        return handlePostRequest(data);
    } else if (method == "PUT") {
        return handlePutRequest(data);
    } else if (method == "DELETE") {
        return handleDeleteRequest(data);
    } else {
        return "Unsupported HTTP method: " + method;
    }
}