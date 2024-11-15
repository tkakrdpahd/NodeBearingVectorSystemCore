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
#include <optional> // For optional return type

#include "NodeVector.h"
#include "BearingVector.h"

class ObjectManager {
private:
    std::vector<std::shared_ptr<NodeVector>> _nodeVectors;
    std::vector<std::shared_ptr<BearingVector>> _bearingVectors;

    // Retrieve NodeVector by index
    std::optional<std::shared_ptr<NodeVector>> GetNodeVectorByIndex(int index) const;
public:
    ObjectManager();
    ~ObjectManager();

    // Create and store a NodeVector
    std::shared_ptr<NodeVector> CreateNodeVector(int index, const Vector3& vector);
    // Read and store a NodeVector
    std::shared_ptr<NodeVector> ReadNodeVector(int index);
    // Update and store a NodeVector
    std::shared_ptr<NodeVector> UpdateNodeVector(int index, const Vector3& vector);
    // Delete a NodeVector
    std::shared_ptr<NodeVector> DeleteNodeVector(int index);

    // Create and store a BearingVector using NodeVector's index & vector.x
    std::shared_ptr<BearingVector> CreateBearingVector(int nodeIndex, const Vector3& force, const Vector3& vector);
    // Read and store a BearingVector using NodeVector's index & vector.x
    std::shared_ptr<BearingVector> ReadBearingVector(int nodeIndex, const Vector3& vector);
    // Update and store a BearingVector using NodeVector's index & vector.x
    std::shared_ptr<BearingVector> UpdateBearingVector(int nodeIndex, const Vector3& force, const Vector3& vector);
    // Delete a BearingVector using NodeVector's index & vector.x
    std::shared_ptr<BearingVector> DeleteBearingVector(int nodeIndex, const Vector3& vector);
};

#endif // OBJECTMANAGER_H
