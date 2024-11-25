/**
 * ServerManager.h
 */

#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include <drogon/drogon.h>

#include "SocketManager.h"
#include "RoutesManager.h"

class ServerManager {
private:
    /* data */
    SocketManager _socketManager;
    RoutesManager _routesManager;
public:
    void Run(){drogon::app().run();};
    void Quit(){drogon::app().quit();};
    
    ServerManager(/* args */);
    ~ServerManager();
};

#endif // SERVERMANAGER_H
