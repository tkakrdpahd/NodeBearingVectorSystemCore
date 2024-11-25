// LinearSegmentDTO.h
#include <iostream>

#include "CoordinateConverter.h"
#include "Vector3.h"
#include "NodeVector.h"
#include "BearingVector.h"
#include "Vertex.h"
#include "LinearSegment.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class LinearSegmentDTO {
    private:
        /* data */
    public:
        LinearSegmentDTO(/* args */);
        ~LinearSegmentDTO();
};
