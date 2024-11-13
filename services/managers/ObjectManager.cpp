/**
 * objectManager.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 13, 2024
 * Last Modified: Nov 13, 2024
 * 
 * Purpose: Implementation of ObjectManager methods
 */

#include "ObjectManager.h"

// Constructor
ObjectManager::ObjectManager() = default;

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
    auto node = std::make_shared<NodeVector>(index, vector);
    _nodeVectors.push_back(node);
    return node;  // Return the created NodeVector
}

// Create and store a BearingVector using NodeVector's index
std::shared_ptr<BearingVector> ObjectManager::CreateBearingVector(int nodeIndex, const Vector3& force, const Vector3& vector) {
    // Automatically find the NodeVector by nodeIndex
    auto node = GetNodeVectorByIndex(nodeIndex);
    if (node) {
        int bearingIndex = static_cast<int>(vector.x);  // Use vector.x as the index
        auto bearing = std::make_shared<BearingVector>(bearingIndex, **node, force, vector);
        _bearingVectors.push_back(bearing);
        return bearing;  // Return the created BearingVector
    } else {
        std::cerr << "NodeVector with index " << nodeIndex << " not found." << std::endl;
        return nullptr;
    }
}
