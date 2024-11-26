// LinearSegmentDTO.h
#include <iostream>
#include <string>

#include "Vector3.h"
#include "NodeVector.h"
#include "BearingVector.h"
#include "Vertex.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class LinearSegmentDTO {
    private:
        /* data */
    public:
        // In
        // 1. Capsulate data as vertex.

        // Out
        // 1. Unpack vertex as json.

        LinearSegmentDTO(/* args */);
        ~LinearSegmentDTO();
};
