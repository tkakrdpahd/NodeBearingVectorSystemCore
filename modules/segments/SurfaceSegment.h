/**
 * SurfaceSegment.h
 * Linked file: SurfaceSegment.cpp
 * Security: Confidential
 * Author: Minseok Doo
 * Date: Oct 7, 2024
 * Last Modified: Nov 11, 2024
 * 
 * Purpose of Class:
 * Purpose: Index buffer for LinearSegment and Surface
 * 
 * Equations:
 */
#ifndef SURFACESEGMENT_H
#define SURFACESEGMENT_H

#include <vector>
#include <memory>
#include "NodeVector.h"
#include "BearingVector.h"

/**
 * @brief Class representing a SurfaceSegment.
 */
class SurfaceSegment
{
private:
    int index; ///< Surface index
    int LOD; ///< Level of Detail
    bool isValid; ///< Indicates if the segment's data is up-to-date
    std::shared_ptr<std::vector<NodeVector>> nodes; ///< Nodes associated with the surface segment
    std::shared_ptr<std::vector<BearingVector>> bearings; ///< Bearings associated with the surface segment

    /**
     * @brief Internal method to validate the segment data.
     */
    void validate();

public:
    /**
     * @brief Constructor for SurfaceSegment.
     */
    SurfaceSegment();

    /**
     * @brief Destructor for SurfaceSegment.
     */
    ~SurfaceSegment();

    /**
     * @brief Creates a new surface segment.
     * @return True if creation was successful, false otherwise.
     */
    bool CreateSurfaceSegment();

    /**
     * @brief Reads the details of the surface segment.
     * @return True if the read operation was successful, false otherwise.
     */
    bool ReadSurfaceSegment();

    /**
     * @brief Updates the surface segment details.
     * @return True if the update was successful, false otherwise.
     */
    bool UpdateSurfaceSegment();

    /**
     * @brief Deletes the surface segment.
     * @return True if the delete operation was successful, false otherwise.
     */
    bool DeleteSurfaceSegment();

    /**
     * @brief Marks the segment as invalid to indicate changes.
     */
    void invalidate();

    /**
     * @brief Checks if the segment's data is valid.
     * @return True if the data is valid, false otherwise.
     */
    bool isSegmentValid() const;

    /**
     * @brief Gets the index of the surface segment.
     * @return The index of the surface segment.
     */
    int getIndex() const;

    /**
     * @brief Sets the index of the surface segment.
     * @param newIndex The new index to set.
     */
    void setIndex(int newIndex);

    /**
     * @brief Gets the Level of Detail (LOD) of the surface segment.
     * @return The LOD value.
     */
    int getLOD() const;

    /**
     * @brief Sets the Level of Detail (LOD) of the surface segment.
     * @param newLOD The new LOD to set.
     */
    void setLOD(int newLOD);

    /**
     * @brief Gets the nodes associated with the surface segment.
     * @return Shared pointer to the vector of NodeVector.
     */
    std::shared_ptr<std::vector<NodeVector>> getNodes() const;

    /**
     * @brief Gets the bearings associated with the surface segment.
     * @return Shared pointer to the vector of BearingVector.
     */
    std::shared_ptr<std::vector<BearingVector>> getBearings() const;
};

#endif // SURFACESEGMENT_H
