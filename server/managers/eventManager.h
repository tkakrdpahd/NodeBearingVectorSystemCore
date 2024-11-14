/**
 * eventManager.h
 * Linked File: eventManager.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 13, 2024
 * Last Modified: Nov 13, 2024
 * 
 * Purpose:
 * /api GET, POST, PUT, DELETE
 */

#pragma once

#include <string>
#include <iostream>

#include "CloseServer.h"
#include "GetAllData.h"
#include "PostAllData.h"
#include "PutAllData.h"
#include "DeleteAllData.h"

class EventManager {
    private:
        std::string handleGetRequest(const std::string& data);
        std::string handlePostRequest(const std::string& data);
        std::string handlePutRequest(const std::string& data);
        std::string handleDeleteRequest(const std::string& data);

    public:
        EventManager();
        ~EventManager();
        
        std::string processRequest(const std::string& method, const std::string& data); // Now returns std::string
};
