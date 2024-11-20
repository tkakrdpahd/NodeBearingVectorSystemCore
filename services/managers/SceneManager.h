/**
 * sceneManager.h
 * Linked File: sceneManager.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Nov 13, 2024
 * Last Modified: Nov 19, 2024
 * 
 * Purpose: Manage objectManager
 * CRUD objectManager instance
 */

#include <string>
#include <iostream>
#include <vector>
#include "ObjectManager.h"

class SceneManager
{
private:
    std::string user;
    std::string date;
    std::shared_ptr<std::vector<ObjectManager>> _objects; // ObjectManager container
public:
    bool CreateSceneManager();
    bool ReadSceneManager();
    bool UpdateSceneManager();
    bool DeleteSceneManager();

    SceneManager(/* args */);
    ~SceneManager();
};

SceneManager::SceneManager(/* args */)
{
}

SceneManager::~SceneManager()
{
}
