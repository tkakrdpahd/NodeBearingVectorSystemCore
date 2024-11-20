/**
 * SceneManager.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 17, 2024
 * Last Modified: Nov 19, 2024
 * 
 */

#include "SceneManager.h"

// Constructor
SceneManager::SceneManager(const std::string& userName, const std::string& creationDate)
    : user(userName), date(creationDate), _objects(std::make_unique<std::vector<std::unique_ptr<ObjectManager>>>())
{
    std::cout << "SceneManager created by " << user << " on " << date << "." << std::endl;
}

// Destructor
SceneManager::~SceneManager()
{
    std::cout << "SceneManager destroyed." << std::endl;
}

// Create a new ObjectManager and add to the container
bool SceneManager::CreateObjectManager(const std::string& objectName)
{
    try
    {
        // Create a new ObjectManager instance with the given name
        std::unique_ptr<ObjectManager> newObject = std::make_unique<ObjectManager>(objectName);
        
        // 예시로 NodeVector와 BearingVector를 추가 (실제 프로젝트 요구사항에 따라 수정 필요)
        newObject->createNodeVector(1, Vector3(0.0f, 0.0f, 0.0f));
        newObject->createBearingVector(NodeVector(1, Vector3(0.0f, 0.0f, 0.0f)), Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
        
        _objects->push_back(std::move(newObject));
        std::cout << "ObjectManager '" << objectName << "' created." << std::endl;
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Failed to create ObjectManager: " << e.what() << std::endl;
        return false;
    }
}

// Read an ObjectManager by ID
ObjectManager* SceneManager::ReadObjectManager(int objectId) const
{
    for (const auto& obj : *_objects)
    {
        auto node = obj->readNodeVector(objectId);
        if (node.has_value()) {
            std::cout << "ObjectManager found: ID " << objectId << ", Name: " << obj->GetName() << "." << std::endl;
            return obj.get();
        }
    }
    std::cerr << "ObjectManager with ID " << objectId << " not found." << std::endl;
    return nullptr;
}

// Update an ObjectManager's name by ID
bool SceneManager::UpdateObjectManager(int objectId, const std::string& newName)
{
    ObjectManager* obj = ReadObjectManager(objectId);
    if (obj)
    {
        obj->SetName(newName);
        std::cout << "ObjectManager ID " << objectId << " updated to Name: " << newName << "." << std::endl;
        return true;
    }
    std::cerr << "Failed to update ObjectManager with ID " << objectId << "." << std::endl;
    return false;
}

// Delete an ObjectManager by ID
bool SceneManager::DeleteObjectManager(int objectId)
{
    for (auto it = _objects->begin(); it != _objects->end(); ++it)
    {
        auto node = (*it)->readNodeVector(objectId);
        if (node.has_value()) {
            std::cout << "Deleting ObjectManager ID " << objectId << ", Name: " << (*it)->GetName() << "." << std::endl;
            _objects->erase(it);
            return true;
        }
    }
    std::cerr << "Failed to delete ObjectManager with ID " << objectId << " - not found." << std::endl;
    return false;
}

// List all ObjectManagers
void SceneManager::ListAllObjectManagers() const
{
    if (_objects->empty())
    {
        std::cout << "No ObjectManagers available." << std::endl;
        return;
    }

    std::cout << "Listing all ObjectManagers:" << std::endl;
    for (const auto& obj : *_objects)
    {
        std::cout << *obj << std::endl; // operator<< 오버로드 사용
    }
}

// Getters
std::string SceneManager::GetUser() const
{
    return user;
}

std::string SceneManager::GetDate() const
{
    return date;
}

// Setters
void SceneManager::SetUser(const std::string& newUser)
{
    user = newUser;
    std::cout << "SceneManager user updated to " << user << "." << std::endl;
}

void SceneManager::SetDate(const std::string& newDate)
{
    date = newDate;
    std::cout << "SceneManager date updated to " << date << "." << std::endl;
}
