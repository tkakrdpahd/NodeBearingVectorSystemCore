/**
 * objectManager.h; formerly attributeManager.h
 * Linked File: objectManager.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 13, 2024
 * Last Modified: Nov 13, 2024
 * 
 * Purpose: Manage Vector, Segment Attributes
 * CRUD Vector Attributes
 */

#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <vector>
#include <memory>
#include <iostream>

#include "NodeVector.h"
#include "BearingVector.h"

class ObjectManager {
private:
    std::vector<std::shared_ptr<NodeVector>> _nodeVectors;
    std::vector<std::shared_ptr<BearingVector>> _bearingVectors;

public:
    ObjectManager() = default;
    ~ObjectManager() {
        std::cout << "ObjectManager is being destroyed. Cleaning up resources." << std::endl;
    }

    // Create and store a NodeVector
    std::shared_ptr<NodeVector> CreateNodeVector(int index, const Vector3& vector) {
        auto node = std::make_shared<NodeVector>(index, vector);
        _nodeVectors.push_back(node);
        return node;  // Return the created NodeVector
    }

    // Create and store a BearingVector
    std::shared_ptr<BearingVector> CreateBearingVector(int index, std::shared_ptr<NodeVector> node, const Vector3& force, const Vector3& vector) {
        auto bearing = std::make_shared<BearingVector>(index, *node, force, vector);
        _bearingVectors.push_back(bearing);
        return bearing;  // Return the created BearingVector
    }
};

#endif // OBJECTMANAGER_H

