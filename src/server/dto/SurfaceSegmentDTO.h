/**
 * SurfaceSegmentDTO.h
 * Author: Minseok Doo
 * Date: 2024-11-26
 * Description: SurfaceSegmentDTO class for handling SurfaceSegment data in JSON format
 */

#ifndef SURFACESEGMENTDTO_H
#define SURFACESEGMENTDTO_H

#include "SurfaceSegment.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class SurfaceSegmentDTO {
    private:
        /* data */
    public:
        SurfaceSegmentDTO(/* args */);
        ~SurfaceSegmentDTO();
};

#endif // SURFACESEGMENTDTO_H