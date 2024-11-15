/**
 * sceneManager.h
 * Linked File: sceneManager.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Nov 13, 2024
 * Last Modified: Nov 13, 2024
 * 
 * Purpose: Manage objectManager
 * CRUD objectManager instance
 */

#include "ObjectManager.h"

class SceneManager {
    private:
        std::vector<std::shared_ptr<ObjectManager>> _ObjectManagers;
    public:
        SceneManager(/* args */);
        ~SceneManager();
        std::shared_ptr<ObjectManager> CreateObject(int index);
        std::shared_ptr<ObjectManager> ReadObject(int index);
        std::shared_ptr<ObjectManager> UpdateObject(int index);
        std::shared_ptr<ObjectManager> DeleteObject(int index);
};

SceneManager::SceneManager(/* args */) {
}

SceneManager::~SceneManager() {
}
