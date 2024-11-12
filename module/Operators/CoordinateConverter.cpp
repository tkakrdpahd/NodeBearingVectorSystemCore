/**
 * CoordinateConverter.cpp
 * Linked file: CoordinateConverter.h
 * Security: Confidential
 * Author: Minseok Doo
 * Date: Oct 7, 2024
 * Last Modified: Nov 11, 2024
 */

#include "CoordinateConverter.h"

/**
 * @brief Converts spherical coordinates to Cartesian coordinates.
 * 
 * Equations:
 * Equ(1): x = r * sin(phi) * cos(theta)
 * Equ(2): y = r * sin(phi) * sin(theta)
 * Equ(3): z = r * cos(phi)
 * 
 * @param sv Vector3 representing spherical coordinates (sv.x = r, sv.y = theta, sv.z = phi).
 * @return Vector3 The converted Cartesian coordinates (x, y, z).
 */
Vector3 CoordinateConverter::sphericalToCartesian(const Vector3& sv) {
    float r = sv.x;
    float theta = sv.y;
    float phi = sv.z;

    float x = r * std::sin(phi) * std::cos(theta);
    float y = r * std::sin(phi) * std::sin(theta);
    float z = r * std::cos(phi);
    return Vector3(x, y, z);
}

/**
 * @brief Converts Cartesian coordinates to spherical coordinates.
 * 
 * Equations:
 * Equ(1): r = sqrt(x^2 + y^2 + z^2)
 * Equ(2): theta = atan2(y, x)
 * Equ(3): phi = acos(z / r)
 * 
 * @param cv Vector3 representing Cartesian coordinates (x, y, z).
 * @return Vector3 The converted spherical coordinates (x = r, y = theta, z = phi).
 */
Vector3 CoordinateConverter::cartesianToSpherical(const Vector3& cv) {
    float x = cv.x;
    float y = cv.y;
    float z = cv.z;

    float r = std::sqrt(x * x + y * y + z * z);
    float theta = (x == 0.0f && y == 0.0f) ? 0.0f : std::atan2(y, x);
    float phi = (r == 0.0f) ? 0.0f : std::acos(z / r);
    return Vector3(r, theta, phi);
}
