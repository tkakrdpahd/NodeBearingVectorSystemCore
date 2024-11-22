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
 * Equ(1): \quad \overline{AB} = \sum_{i=1}^N ab_i' \\
 * Equ(2): \quad \overline{BC} = \sum_{i=1}^N bc_i' \\
 * Equ(3): \quad \overline{AC} = \sum_{i=1}^N ac_i' \\
 * Equ(4): \quad t_i = \frac{i}{N}, \quad i = 0, 1, 2, \dots, N \\
 * Equ(5): \quad P_{AB}(t_i) = A + t_i (B - A) \\
 * Equ(6): \quad P_{BC}(t_i) = B + t_i (C - B) \\
 * Equ(7): \quad P_{AC}(t_i) = A + t_i (C - A) \\
 * Equ(8): \quad L_{nn_i}(s) = P_{AB}(t_i) + s \big( P_{BC}(t_i) - P_{AB}(t_i) \big), \quad s \in [0, 1] \\
 * Equ(9): \quad L_{AC}(r) = A + r (C - A), \quad r \in [0, 1] \\
 * Equ(10): \quad P_{AB}(t_i) + s \big( P_{BC}(t_i) - P_{AB}(t_i) \big) = A + r (C - A)
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
    
    // 출력 연산자 오버로드 선언
    friend std::ostream& operator<<(std::ostream& os, const SurfaceSegment& ss);
};

#endif // SURFACESEGMENT_H
