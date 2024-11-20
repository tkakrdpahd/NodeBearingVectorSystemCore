/**
 * SceneManager.h
 * Linked File: SceneManager.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Nov 13, 2024
 * Last Modified: Nov 19, 2024
 * 
 * Purpose: Manage ObjectManager instances
 * Provides CRUD operations for ObjectManager
 */

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "ObjectManager.h"

class SceneManager
{
private:
    std::string user;
    std::string date;
    std::unique_ptr<std::vector<std::unique_ptr<ObjectManager>>> _objects; // ObjectManager 컨테이너

public:
    // Constructors and Destructors
    SceneManager(const std::string& userName, const std::string& creationDate);
    ~SceneManager();

    // CRUD Operations for ObjectManager
    bool CreateObjectManager(const std::string& objectName);
    ObjectManager* ReadObjectManager(int objectId) const;
    bool UpdateObjectManager(int objectId, const std::string& newName);
    bool DeleteObjectManager(int objectId);

    // Utility Methods
    void ListAllObjectManagers() const;

    // Getters
    std::string GetUser() const;
    std::string GetDate() const;

    // Setters
    void SetUser(const std::string& newUser);
    void SetDate(const std::string& newDate);
};

#endif // SCENEMANAGER_H
