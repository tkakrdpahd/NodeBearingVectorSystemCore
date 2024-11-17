/**
 * BearingVector.h
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 7, 2024
 * Last Modified: Nov 16, 2024
 * 
 * Purpose: Implementation of the BearingVector class methods
 */

#include "Vector3.h"
#include "CoordinateConverter.h"

/**
 * @brief Bearing Vector
 * 
 * @param NodeIndex Patrent Node Vector Index
 * @param Force Bearing Vector Force; (x, y, z)
 * @param Vector Bearing Vector location; (x, y, z), (r_i, theta_i, phi_i)
 */
struct BearingVector
{
    int NodeIndex;
    Vector3 Force;
    Vector3 Vector;
};
