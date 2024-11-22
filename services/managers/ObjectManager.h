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
#include <iostream> // For operator<<

#include "Vector3.h"
#include "NodeVector.h"
#include "BearingVector.h"
#include "LinearSegment.h"
// #include "SurfaceSegment.h"

#include "JsonConverter.h"

/**
 * @brief ObjectManager for maintaining the object information.
 * 
 * @param index Index of ObjectManager.
 * @param max Maximum value of object value; for normalized fixed point calculation.
 * @param min Minimum value of object value; for normalized fixed point calculation.
 */
class ObjectManager {
private:
    int index;
    float max, min;
    std::string name; // Added name member variable
    std::unique_ptr<std::vector<NodeVector>> nodeVectors;
    std::unique_ptr<std::vector<BearingVector>> bearingVectors;
    std::unique_ptr<std::vector<LinearSegment>> linearSegments;
    // std::unique_ptr<std::vector<SurfaceSegment>> surfaceSegments;

    // 특정 인덱스 찾기 (NodeVector)
    template <typename T>
    std::optional<size_t> findIndexById(const std::vector<T>& collection, int id) const;

public:
    ObjectManager(const std::string& managerName = "DefaultManager");
    ~ObjectManager();

    // Getters and Setters for name
    std::string GetName() const;
    void SetName(const std::string& newName);

    // NodeVector Methods
    bool createNodeVector(int id, const Vector3& position);
    std::optional<NodeVector> readNodeVector(int id) const;
    bool updateNodeVector(int id, const Vector3& newPosition);
    bool deleteNodeVector(int id);

    // BearingVector Methods
    bool createBearingVector(const NodeVector& node, const Vector3& force, const Vector3& vector);
    std::optional<BearingVector> readBearingVector(const NodeVector& node) const;
    bool updateBearingVector(const NodeVector& node, const Vector3& newForce);
    bool deleteBearingVector(const NodeVector& node);

    // LinearSegment Methods
    bool createLinearSegment(const NodeVector& startNode, const std::vector<BearingVector>& startBearing,
                             const NodeVector& endNode, const std::vector<BearingVector>& endBearing);
    std::vector<LinearSegment> readAllLinearSegments() const;
    bool deleteLinearSegment(const NodeVector& startNode, const NodeVector& endNode);

    // SurfaceSegment Methods
    // bool createSurfaceSegment(int id);
    // std::vector<SurfaceSegment> readAllSurfaceSegments() const;
    // bool deleteSurfaceSegment(int id);

    // Manager Functions
    void SaveAll();
    void DeleteAll();

    // 출력 연산자 오버로드 선언
    friend std::ostream& operator<<(std::ostream& os, const ObjectManager& obj);
};

// 템플릿 메서드는 헤더에 정의되어야 합니다.
template <typename T>
std::optional<size_t> ObjectManager::findIndexById(const std::vector<T>& collection, int id) const {
    for (size_t i = 0; i < collection.size(); ++i) {
        if (collection[i].Index == id) { // NodeVector의 Index를 직접 접근
            return i;
        }
    }
    return std::nullopt;
}

#endif // OBJECTMANAGER_H
