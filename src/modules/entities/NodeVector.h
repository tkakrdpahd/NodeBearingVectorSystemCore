/**
 * NodeVector.h
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 7, 2024
 * Last Modified: Nov 16, 2024
 * 
 * This header file defines the NodeVector structure which represents a node in 3D space.
 * It combines an index identifier with a 3D vector position.
 */

#ifndef NODEVECTOR_H
#define NODEVECTOR_H

// Include JSON library for serialization/deserialization
#include <nlohmann/json.hpp>
using json = nlohmann::json;

// Include Vector3 for 3D position representation
#include "Vector3.h"

/**
 * @brief Node Vector structure representing a node with position in 3D space
 * 
 * @param Index Node Vector index - unique identifier for the node
 * @param Vector Node Vector location in either:
 *        - Cartesian coordinates (x, y, z)
 *        - Spherical coordinates (r_i, theta_i, phi_i)
 */
struct NodeVector
{
    // Unique identifier for the node
    int Index;
    
    // 3D position vector of the node
    Vector3 Vector;

    /**
     * @brief Constructs a NodeVector with an ID and position
     * @param nodeId Unique identifier for the node
     * @param vec 3D position vector
     */
    NodeVector(int nodeId, const Vector3& vec) : Index(nodeId), Vector(vec) {}

    /**
     * @brief Serializes the NodeVector to JSON format
     * @return JSON object containing the node data
     */
    json toJson() const {
        return {
            {"index", Index},
            {"vector", Vector.toJson()}
        };
    }

    /**
     * @brief Creates a NodeVector from JSON data
     * @param j JSON object containing node data
     * @return Constructed NodeVector instance
     */
    static NodeVector fromJson(const json& j) {
        return NodeVector(
            j["index"].get<int>(),
            Vector3::fromJson(j["vector"])
        );
    }

    /**
     * @brief Overloaded output operator for string representation
     * @param os Output stream
     * @param nv NodeVector to output
     * @return Reference to output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const NodeVector& nv) {
        os << "NodeVector(Index: " << nv.Index << ", Vector: " << nv.Vector << ")";
        return os;
    }
};

#endif // NODEVECTOR_H