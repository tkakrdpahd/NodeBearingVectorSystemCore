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

// Constructor and Destructor
ObjectManager::ObjectManager()
    : nodeVectors(std::make_shared<std::vector<NodeVector>>()),
      bearingVectors(std::make_shared<std::vector<BearingVector>>()),
      LinearSegments(std::make_shared<std::vector<LinearSegment>>()) {}

ObjectManager::~ObjectManager() {}

// Find index by integer ID (NodeVector and similar)
template <typename T>
std::optional<size_t> ObjectManager::findIndexById(const std::vector<T>& collection, int id) const {
    for (size_t i = 0; i < collection.size(); ++i) {
        if (collection[i].Index == id) {
            return i;
        }
    }
    return std::nullopt;
}

// Find index by float ID (BearingVector)
std::optional<size_t> ObjectManager::findBearingVectorIndex(float id) const {
    for (size_t i = 0; i < bearingVectors->size(); ++i) {
        if (std::abs((*bearingVectors)[i].Vector.x - id) < 1e-6) {
            return i;
        }
    }
    return std::nullopt;
}

// NodeVector Methods
bool ObjectManager::createNodeVector(int id, const Vector3& position) {
    if (findIndexById(*nodeVectors, id)) return false;
    nodeVectors->emplace_back(id, position);
    return true;
}

std::optional<NodeVector> ObjectManager::readNodeVector(int id) const {
    auto index = findIndexById(*nodeVectors, id);
    if (index) return (*nodeVectors)[*index];
    return std::nullopt;
}

bool ObjectManager::updateNodeVector(int id, const Vector3& newPosition) {
    auto index = findIndexById(*nodeVectors, id);
    if (!index) return false;
    (*nodeVectors)[*index].Vector = newPosition;
    return true;
}

bool ObjectManager::deleteNodeVector(int id) {
    auto index = findIndexById(*nodeVectors, id);
    if (!index) return false;
    nodeVectors->erase(nodeVectors->begin() + *index);
    return true;
}

// BearingVector Methods
bool ObjectManager::createBearingVector(const NodeVector& node, const Vector3& force, const Vector3& vector) {
    if (findBearingVectorIndex(vector.x)) return false;
    bearingVectors->emplace_back(node, force, vector);
    return true;
}

std::optional<BearingVector> ObjectManager::readBearingVector(float id) const {
    auto index = findBearingVectorIndex(id);
    if (index) return (*bearingVectors)[*index];
    return std::nullopt;
}

bool ObjectManager::updateBearingVector(float id, const Vector3& newForce) {
    auto index = findBearingVectorIndex(id);
    if (!index) return false;
    (*bearingVectors)[*index].Force = newForce;
    return true;
}

bool ObjectManager::deleteBearingVector(float id) {
    auto index = findBearingVectorIndex(id);
    if (!index) return false;
    bearingVectors->erase(bearingVectors->begin() + *index);
    return true;
}

// LinearSegment Methods
bool ObjectManager::createLinearSegment(const NodeVector& startNode, const std::vector<BearingVector>& startBearing,
                                       const NodeVector& endNode, const std::vector<BearingVector>& endBearing) {
    LinearSegments->emplace_back(startNode, startBearing, endNode, endBearing);
    return true;
}

std::vector<LinearSegment> ObjectManager::readAllLinearSegments() const {
    return *LinearSegments;
}

bool ObjectManager::deleteLinearSegment(const NodeVector& startNode, const NodeVector& endNode) {
    auto it = std::remove_if(LinearSegments->begin(), LinearSegments->end(),
                             [&](const LinearSegment& segment) {
                                 return segment.NodeStart.Index == startNode.Index &&
                                        segment.NodeEnd.Index == endNode.Index;
                             });
    if (it == LinearSegments->end()) return false;
    LinearSegments->erase(it, LinearSegments->end());
    return true;
}
