/**
 * SurfaceSegment.h
 * 
 * Purpose: Index buffer for Linersegment and Surface
 */

#include <vector>

#include "NodeVector.h"
#include "BearingVector.h"

class SurfaceSegment
{
private:
    int index;
    int LOD;
    bool isValid;
    std::shared_ptr<std::vector<NodeVector>>& nodes; // Use node.index;
    std::shared_ptr<std::vector<BearingVector>>& bearings; // Use bearing.vector.x for index;
public:
    SurfaceSegment(/* args */);
    ~SurfaceSegment();
};
