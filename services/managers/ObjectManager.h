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
#include <iostream>
#include <optional>

#include "Vector3.h"
#include "NodeVector.h"
#include "BearingVector.h"
#include "LinerSegment.h"

class ObjectManager {
private:
    // Containers to store NodeVectors, BearingVectors, LinerSegments and SurfaceSegments
    std::vector<std::shared_ptr<NodeVector>> _nodeVectors;
    std::vector<std::shared_ptr<BearingVector>> _bearingVectors;
    std::vector<std::shared_ptr<LinerSegment>> _linerSegments;

    /**
     * @brief Retrieve a NodeVector by its index.
     * 
     * @param index The index of the NodeVector to retrieve.
     * @return std::optional<std::shared_ptr<NodeVector>> The found NodeVector or std::nullopt if not found.
     */
    std::optional<std::shared_ptr<NodeVector>> GetNodeVectorByIndex(int index) const;

public:
    /**
     * @brief Default constructor.
     */
    ObjectManager();

    /**
     * @brief Destructor. Cleans up resources.
     */
    ~ObjectManager();

    // CRUD operations for NodeVector

    /**
     * @brief Create and store a new NodeVector.
     * 
     * @param index The index of the new NodeVector.
     * @param vector The Vector3 data for the new NodeVector.
     * @return std::shared_ptr<NodeVector> The created NodeVector.
     */
    std::shared_ptr<NodeVector> CreateNodeVector(int index, const Vector3& vector);

    /**
     * @brief Read a NodeVector by its index.
     * 
     * @param index The index of the NodeVector to read.
     * @return std::shared_ptr<NodeVector> The found NodeVector or nullptr if not found.
     */
    std::shared_ptr<NodeVector> ReadNodeVector(int index);

    /**
     * @brief Update an existing NodeVector.
     * 
     * @param index The index of the NodeVector to update.
     * @param vector The new Vector3 data.
     * @return std::shared_ptr<NodeVector> The updated NodeVector or nullptr if not found.
     */
    std::shared_ptr<NodeVector> UpdateNodeVector(int index, const Vector3& vector);

    /**
     * @brief Delete a NodeVector by its index.
     * 
     * @param index The index of the NodeVector to delete.
     * @return std::shared_ptr<NodeVector> The deleted NodeVector or nullptr if not found.
     */
    std::shared_ptr<NodeVector> DeleteNodeVector(int index);

    // CRUD operations for BearingVector

    /**
     * @brief Create and store a new BearingVector.
     * 
     * @param nodeIndex The index of the associated NodeVector.
     * @param force The force Vector3.
     * @param vector The Vector3 data for the BearingVector.
     * @return std::shared_ptr<BearingVector> The created BearingVector or nullptr if associated NodeVector not found.
     */
    std::shared_ptr<BearingVector> CreateBearingVector(int nodeIndex, const Vector3& force, const Vector3& vector);

    /**
     * @brief Read a BearingVector by associated NodeVector's index and vector.x.
     * 
     * @param nodeIndex The index of the associated NodeVector.
     * @param vector The Vector3 data to identify the BearingVector.
     * @return std::shared_ptr<BearingVector> The found BearingVector or nullptr if not found.
     */
    std::shared_ptr<BearingVector> ReadBearingVector(int nodeIndex, const Vector3& vector);

    /**
     * @brief Update an existing BearingVector.
     * 
     * @param nodeIndex The index of the associated NodeVector.
     * @param force The new force Vector3.
     * @param vector The new Vector3 data for the BearingVector.
     * @return std::shared_ptr<BearingVector> The updated BearingVector or nullptr if not found.
     */
    std::shared_ptr<BearingVector> UpdateBearingVector(int nodeIndex, const Vector3& force, const Vector3& vector);

    /**
     * @brief Delete a BearingVector by associated NodeVector's index and vector.x.
     * 
     * @param nodeIndex The index of the associated NodeVector.
     * @param vector The Vector3 data to identify the BearingVector.
     * @return std::shared_ptr<BearingVector> The deleted BearingVector or nullptr if not found.
     */
    std::shared_ptr<BearingVector> DeleteBearingVector(int nodeIndex, const Vector3& vector);
};

#endif // OBJECTMANAGER_H
