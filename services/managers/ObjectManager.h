/**
 * ObjectManager.h
 * Formerly attributeManager.h
 * Linked File: ObjectManager.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 13, 2024
 * Last Modified: Nov 16, 2024
 * 
 * Purpose: Manage Vector and Segment Attributes
 * Provides CRUD operations for Vector Attributes
 */

#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <vector>
#include <memory>
#include <optional>

#include "Vector3.h"
#include "NodeVector.h"
#include "BearingVector.h"
#include "LinearSegment.h"
#include "SurfaceSegment.h"

/**
 * @brief ObjectManager for maintain the object information.
 * 
 * @param index index of ObjectManager.
 * @param max maximum value of object value; for normalized fixed point calculation.
 * @param min minimum value of object value; for normalized fixed point calculation.
 */
class ObjectManager {
private:
    int index;
    float max, min;
    std::shared_ptr<std::vector<NodeVector>> nodeVectors;
    std::shared_ptr<std::vector<BearingVector>> bearingVectors;
    std::shared_ptr<std::vector<LinerSegment>> linerSegments;
    std::shared_ptr<std::vector<SurfaceSegment>> _surfaceSegment;

    // 특정 인덱스 찾기 (NodeVector)
    template <typename T>
    std::optional<size_t> findIndexById(const std::vector<T>& collection, int id) const;

    // 특정 인덱스 찾기 (BearingVector - Vector.x 기준)
    std::optional<size_t> findBearingVectorIndex(float id) const;

public:
    ObjectManager();
    ~ObjectManager();

    // NodeVector Methods
    bool createNodeVector(int id, const Vector3& position);
    std::optional<NodeVector> readNodeVector(int id) const;
    bool updateNodeVector(int id, const Vector3& newPosition);
    bool deleteNodeVector(int id);

    // BearingVector Methods
    bool createBearingVector(const NodeVector& node, const Vector3& force, const Vector3& vector);
    std::optional<BearingVector> readBearingVector(float id) const;
    bool updateBearingVector(float id, const Vector3& newForce);
    bool deleteBearingVector(float id);

    // LinerSegment Methods
    bool createLinerSegment(const NodeVector& startNode, const std::vector<BearingVector>& startBearing,
                            const NodeVector& endNode, const std::vector<BearingVector>& endBearing);
    std::vector<LinerSegment> readAllLinerSegments() const;
    bool deleteLinerSegment(const NodeVector& startNode, const NodeVector& endNode);
};

#endif // OBJECTMANAGER_H
