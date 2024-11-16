/**
 * CoordinateConverter.cpp
 * Linked file: CoordinateConverter.h
 * Security: Confidential
 * Author: Minseok Doo
 * Date: Oct 7, 2024
 */

#include "CoordinateConverter.h"
#include "Vector3.h"

/**
 * @brief Converts a SphericalVector to a CartesianVector.
 * 
 * Equations:
 * Equ(1): x = r * sin(phi) * cos(theta)
 * Equ(2): y = r * sin(phi) * sin(theta)
 * Equ(3): z = r * cos(phi)
 * 
 * @param sv SphericalVector object to be converted.
 * @return CartesianVector Converted CartesianVector object.
 */
CartesianVector CoordinateConverter::sphericalToCartesian(const SphericalVector& sv) {
    float x = sv.r * std::sin(sv.phi) * std::cos(sv.theta);
    float y = sv.r * std::sin(sv.phi) * std::sin(sv.theta);
    float z = sv.r * std::cos(sv.phi);
    return CartesianVector(x, y, z);
}

/**
 * @brief Converts a CartesianVector to a SphericalVector.
 * 
 * Equations:
 * Equ(1): r = sqrt(x^2 + y^2 + z^2)
 * Equ(2): theta = atan2(y, x)
 * Equ(3): phi = acos(z / r)
 * 
 * @param cv CartesianVector object to be converted.
 * @return SphericalVector Converted SphericalVector object.
 */
SphericalVector CoordinateConverter::cartesianToSpherical(const CartesianVector& cv) {
    float r = std::sqrt(cv.x * cv.x + cv.y * cv.y + cv.z * cv.z);
    float theta = (cv.x == 0.0f && cv.y == 0.0f) ? 0.0f : std::atan2(cv.y, cv.x);
    float phi = (r == 0.0f) ? 0.0f : std::acos(cv.z / r);
    return SphericalVector(r, theta, phi);
}
