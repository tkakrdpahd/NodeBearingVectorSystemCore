/**
 * BearingVectorDTO.h
 * Author: Minseok Doo
 * Date: 2024-11-26
 * Description: BearingVectorDTO class for handling BearingVector data in JSON format
 */

#ifndef BEARINGVECTORDTO_H
#define BEARINGVECTORDTO_H

#include "BearingVector.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class BearingVectorDTO {
    private:
        /* data */
    public:
        BearingVectorDTO(/* args */);
        ~BearingVectorDTO();
};

#endif // BEARINGVECTORDTO_H
