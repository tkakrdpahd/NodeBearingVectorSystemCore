/**
 * ObjectManager.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 13, 2024
 * Last Modified: Nov 16, 2024
 * 
 * Purpose: Implementation of ObjectManager methods
 */

#include "ObjectManager.h"

// Constructor
ObjectManager::ObjectManager() {
    std::cout << "ObjectManager initialized." << std::endl;
}

// Destructor
ObjectManager::~ObjectManager() {
    std::cout << "ObjectManager is being destroyed. Cleaning up resources." << std::endl;
}

// Retrieve NodeVector by index
std::optional<std::shared_ptr<NodeVector>> ObjectManager::GetNodeVectorByIndex(int index) const {
    for (const auto& node : _nodeVectors) {
        if (node->index == index) {
            return node; // Found NodeVector with the specified index
        }
    }
    return std::nullopt; // Return empty optional if index not found
}

// Create and store a NodeVector
std::shared_ptr<NodeVector> ObjectManager::CreateNodeVector(int index, const Vector3& vector) {
    // Check if a NodeVector with the same index already exists
    auto existingNode = GetNodeVectorByIndex(index);
    if (existingNode) {
        std::cerr << "NodeVector with index " << index << " already exists. Creation aborted." << std::endl;
        return nullptr;
    }

    auto node = std::make_shared<NodeVector>(index, vector);
    _nodeVectors.push_back(node);
    std::cout << "Created NodeVector with index " << index << "." << std::endl;
    return node;  // Return the created NodeVector
}

// Read a NodeVector by index
std::shared_ptr<NodeVector> ObjectManager::ReadNodeVector(int index) {
    auto nodeOpt = GetNodeVectorByIndex(index);
    if (nodeOpt) {
        std::cout << "Read NodeVector with index " << index << "." << std::endl;
        return *nodeOpt;
    } else {
        std::cerr << "NodeVector with index " << index << " not found." << std::endl;
        return nullptr;
    }
}

// Update a NodeVector by index
std::shared_ptr<NodeVector> ObjectManager::UpdateNodeVector(int index, const Vector3& vector) {
    auto nodeOpt = GetNodeVectorByIndex(index);
    if (nodeOpt) {
        auto node = *nodeOpt;
        node->vector = vector; // Assuming NodeVector has a 'vector' member of type Vector3
        std::cout << "Updated NodeVector with index " << index << "." << std::endl;
        return node;
    } else {
        std::cerr << "NodeVector with index " << index << " not found. Update failed." << std::endl;
        return nullptr;
    }
}

// Delete a NodeVector by index
std::shared_ptr<NodeVector> ObjectManager::DeleteNodeVector(int index) {
    for (auto it = _nodeVectors.begin(); it != _nodeVectors.end(); ++it) {
        if ((*it)->index == index) {
            auto deletedNode = *it;
            _nodeVectors.erase(it);
            std::cout << "Deleted NodeVector with index " << index << "." << std::endl;
            return deletedNode;
        }
    }
    std::cerr << "NodeVector with index " << index << " not found. Deletion failed." << std::endl;
    return nullptr;
}

// Create and store a BearingVector using NodeVector's index
std::shared_ptr<BearingVector> ObjectManager::CreateBearingVector(int nodeIndex, const Vector3& force, const Vector3& vector) {
    // Automatically find the NodeVector by nodeIndex
    auto nodeOpt = GetNodeVectorByIndex(nodeIndex);
    if (nodeOpt) {
        auto node = *nodeOpt;
        int bearingIndex = static_cast<int>(vector.x);  // Use vector.x as the index

        // Check if a BearingVector with the same identifier already exists
        for (const auto& bearing : _bearingVectors) {
            if (bearing->getNodeVector().index == nodeIndex && bearing->vector.x == vector.x) {
                std::cerr << "BearingVector with nodeIndex " << nodeIndex << " and vector.x " << vector.x << " already exists. Creation aborted." << std::endl;
                return nullptr;
            }
        }

        auto bearing = std::make_shared<BearingVector>(bearingIndex, *node, force, vector);
        _bearingVectors.push_back(bearing);
        std::cout << "Created BearingVector with nodeIndex " << nodeIndex << " and vector.x " << vector.x << "." << std::endl;
        return bearing;  // Return the created BearingVector
    } else {
        std::cerr << "NodeVector with index " << nodeIndex << " not found. BearingVector creation failed." << std::endl;
        return nullptr;
    }
}

// Read a BearingVector by nodeIndex and vector.x
std::shared_ptr<BearingVector> ObjectManager::ReadBearingVector(int nodeIndex, const Vector3& vector) {
    for (const auto& bearing : _bearingVectors) {
        if (bearing->getNodeVector().index == nodeIndex && bearing->vector.x == vector.x) {
            std::cout << "Read BearingVector with nodeIndex " << nodeIndex << " and vector.x " << vector.x << "." << std::endl;
            return bearing;
        }
    }
    std::cerr << "BearingVector with nodeIndex " << nodeIndex << " and vector.x " << vector.x << " not found." << std::endl;
    return nullptr;
}

// Update a BearingVector by nodeIndex and vector.x
std::shared_ptr<BearingVector> ObjectManager::UpdateBearingVector(int nodeIndex, const Vector3& force, const Vector3& vector) {
    for (auto& bearing : _bearingVectors) {
        if (bearing->getNodeVector().index == nodeIndex && bearing->vector.x == vector.x) {
            bearing->force = force;   // Assuming BearingVector has a 'force' member of type Vector3
            bearing->vector = vector; // Update the vector as well if needed
            std::cout << "Updated BearingVector with nodeIndex " << nodeIndex << " and vector.x " << vector.x << "." << std::endl;
            return bearing;
        }
    }
    std::cerr << "BearingVector with nodeIndex " << nodeIndex << " and vector.x " << vector.x << " not found. Update failed." << std::endl;
    return nullptr;
}

// Delete a BearingVector by nodeIndex and vector.x
std::shared_ptr<BearingVector> ObjectManager::DeleteBearingVector(int nodeIndex, const Vector3& vector) {
    for (auto it = _bearingVectors.begin(); it != _bearingVectors.end(); ++it) {
        if ((*it)->getNodeVector().index == nodeIndex && (*it)->vector.x == vector.x) {
            auto deletedBearing = *it;
            _bearingVectors.erase(it);
            std::cout << "Deleted BearingVector with nodeIndex " << nodeIndex << " and vector.x " << vector.x << "." << std::endl;
            return deletedBearing;
        }
    }
    std::cerr << "BearingVector with nodeIndex " << nodeIndex << " and vector.x " << vector.x << " not found. Deletion failed." << std::endl;
    return nullptr;
}
