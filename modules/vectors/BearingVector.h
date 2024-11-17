/**
 * BearingVector.h
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 7, 2024
 * Last Modified: Nov 16, 2024
 * 
 * Purpose: Implementation of the BearingVector class methods
 */
#ifndef BEARINGVECTOR_H
#define BEARINGVECTOR_H

#include "Vector3.h"
#include "NodeVector.h"
#include "CoordinateConverter.h"

/**
 * @brief Bearing Vector
 * 
 * @param NodeVector Patrent Node Vector
 * @param Force Bearing Vector Force; (x, y, z)
 * @param Vector Bearing Vector location; (x, y, z), (d_i, theta_i, phi_i)
 */
struct BearingVector
{
    NodeVector Node;
    Vector3 Force;
    Vector3 Vector;

    BearingVector(const NodeVector& node, const Vector3& force, const Vector3& vec) : Node(node), Force(force), Vector(vec) {}
};

#endif // BEARINGVECTOR_H
