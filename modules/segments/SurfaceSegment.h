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
#include "LinearSegment.h"

/**
 * @brief Class representing a SurfaceSegment.
 */
class SurfaceSegment
{
private:
    int index; ///< Surface index
    bool isValid; ///< Indicates if the segment's data is up-to-date

    std::shared_ptr<std::vector<NodeVector>> nodes; ///< Nodes associated with the surface segment
    std::vector<LinearSegment>& _linearSegmentCache;
    std::shared_ptr<std::vector<Vector3>> _surfaceSegmentCache;
public:
    public:
    /**
     * @brief Constructs a SurfaceSegment with a reference to a LinearSegment cache.
     * 
     * @param linearSegmentCache Reference to a vector of LinearSegment objects.
     */
    SurfaceSegment(std::vector<LinearSegment>& linearSegmentCache)
        : _linearSegmentCache(linearSegmentCache)
    {
        // 초기화가 필요한 다른 멤버들이 있다면 여기서 처리할 수 있습니다.
    }
};

#endif // SURFACESEGMENT_H
