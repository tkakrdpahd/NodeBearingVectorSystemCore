/**
 * NodeVectorDTO.h
 * Author: Minseok Doo
 * Date: 2024-11-26
 * Description: NodeVectorDTO class for handling NodeVector data in JSON format
 */
#ifndef NODEVECTORDTO_H
#define NODEVECTORDTO_H

#include "NodeVector.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class NodeVectorDTO {
    private:
        /* data */
    public:
        NodeVectorDTO(/* args */);
        ~NodeVectorDTO();
};

#endif // NODEVECTORDTO_H