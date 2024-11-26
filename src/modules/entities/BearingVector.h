/**
 * BearingVector.h
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 7, 2024
 * Last Modified: Nov 16, 2024
 * 
 * Purpose: Implementation of the BearingVector class methods
 * 
 * Equations
 * Equ(1): (B_i ) ⃗=(■(sin⁡ϕ_i cos⁡θ_i@sin⁡ϕ_i sin⁡θ_i@cos⁡ϕ_i ))
 * Equ(2): (B_(i,d) ) ⃗=(B_(i,d,x),B_(i,d,y),B_(i,d,z) )
 * Equ(3): (F_i ) ⃗=F_(x_i ) x ̂+F_(y_i ) y ̂+F_(z_i ) z ̂
 * Equ(4): R_i=R_z (θ_i ) R_y (ϕ_i )
 * Equ(5): R_z (θ_i )=(■(cos⁡θ_i & -sin⁡θ_i & 0@sin⁡θ_i & cos⁡θ_i & 0@0 & 0 & 1))
 * Equ(6): R_y (ϕ_i )=(■(cos⁡ϕ_i & 0 & sin⁡ϕ_i@0 & 1 & 0@-sin⁡ϕ_i & 0 & cos⁡ϕ_i ))
 */

#ifndef BEARINGVECTOR_H
#define BEARINGVECTOR_H

// Json
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "Vector3.h"
#include "NodeVector.h"

/**
 * @brief Bearing Vector
 * 
 * @param NodeVector Parent Node Vector
 * @param Force Bearing Vector Force in Cartesian coordinates (x, y, z)
 * @param Vector Bearing Vector location; (x, y, z), (d_i, theta_i, phi_i)
 */
struct BearingVector
{
    NodeVector Node;
    Vector3 Force;    // Always in Cartesian coordinates (x, y, z)
    Vector3 Vector;

    /**
     * @brief Constructs a BearingVector with a parent node, force, and position
     * @param node Parent NodeVector
     * @param force Force vector in Cartesian coordinates (x, y, z)
     * @param vec Position vector (x, y, z) or (d_i, theta_i, phi_i)
     */
    BearingVector(const NodeVector& node, const Vector3& force, const Vector3& vec) 
        : Node(node), Force(force), Vector(vec) {}

    /**
     * @brief Serializes the BearingVector to JSON format
     * @return JSON object containing the bearing vector data
     * @note Force is always stored in Cartesian coordinates
     */
    json toJson() const {
        return {
            {"node", Node.toJson()},
            {"force", {           // Force in Cartesian coordinates
                {"x", Force.x},
                {"y", Force.y},
                {"z", Force.z}
            }},
            {"vector", Vector.toJson()}
        };
    }

    /**
     * @brief Creates a BearingVector from JSON data
     * @param j JSON object containing bearing vector data
     * @return Constructed BearingVector instance
     * @note Force is expected to be in Cartesian coordinates
     */
    static BearingVector fromJson(const json& j) {
        return BearingVector(
            NodeVector::fromJson(j["node"]),
            Vector3(                      // Force in Cartesian coordinates
                j["force"]["x"].get<float>(),
                j["force"]["y"].get<float>(),
                j["force"]["z"].get<float>()
            ),
            Vector3::fromJson(j["vector"])
        );
    }
    
    /**
     * @brief Overloaded output operator for string representation
     * @param os Output stream
     * @param bv BearingVector to output
     * @return Reference to output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const BearingVector& bv) {
        os << "BearingVector(Node: " << bv.Node << ", Force: " << bv.Force << ", Vector: " << bv.Vector << ")";
        return os;
    }
};

#endif // BEARINGVECTOR_H