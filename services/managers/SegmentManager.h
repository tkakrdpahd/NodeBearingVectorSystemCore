/**
 * SegmentManager.h
 * Linked File: SegmentManager.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Nov 23, 2024
 * Last Modified: Nov 23, 2024
 * 
 * Purpose: 
 * Manage LinearSegment, SurfaceSegment and Index Buffer
 * 
 */

#ifndef SEGMENTMANAGER_H
#define SEGMENTMANAGER_H

#include "IndexBuffer.h"
#include "LinearSegment.h"
#include "SurfaceSegment.h"

/**
 * @brief SegmentManager; 6 dimension pointer data storage for manage segments.
 * 
 * Expected input_01 [int lod, std::vector<NodeVector> NodeVector StartNode, NodeVector EndNode, std::vector<BearingVector> BearingVector StartNodeBearing, EndNodeBearing]
 * Expected input_02 [std::vector<NodeVector> NodeVector node01, NodeVector node02, NodeVector node03 ..., std::vector<BearingVector> BearingVector bearing01, bearing02, bearing03 ...]
 */
class SegmentManager
{
private:
    /* data */
public:
    SegmentManager(/* args */);
    ~SegmentManager();
};

#endif // SEGMENTMANAGER_H