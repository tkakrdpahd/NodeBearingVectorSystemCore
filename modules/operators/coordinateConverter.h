/**
 * CoordinateConverter.h
 * Linked file: CoordinateConverter.cpp
 * Security: Confidential
 * Author: Minseok Doo
 * Date: Oct 7, 2024
 * Last Modified: Nov 11, 2024
 * 
 * Purpose of Class:
 * Conversion between spherical coordinates and Cartesian coordinates using Vector3
 * 
 * Equations:
 * Equ(1): x = r * sin(phi) * cos(theta)
 * Equ(2): y = r * sin(phi) * sin(theta)
 * Equ(3): z = r * cos(phi)
 */

#ifndef COORDINATECONVERTER_H
#define COORDINATECONVERTER_H

#include <cmath>
#include "Vector3.h"  // Include the Vector3 header

/**
 * @brief Utility class for converting between spherical and Cartesian coordinates using Vector3.
 */
class CoordinateConverter {
public:
    /**
     * @brief Converts spherical coordinates to Cartesian coordinates.
     * 
     * @param sv Vector3 representing spherical coordinates (sv.x = r, sv.y = theta, sv.z = phi).
     * @return Vector3 The converted Cartesian coordinates (x, y, z).
     */
    static Vector3 sphericalToCartesian(const Vector3& sv);

    /**
     * @brief Converts Cartesian coordinates to spherical coordinates.
     * 
     * @param cv Vector3 representing Cartesian coordinates (x, y, z).
     * @return Vector3 The converted spherical coordinates (x = r, y = theta, z = phi).
     */
    static Vector3 cartesianToSpherical(const Vector3& cv);

    /**
     * @brief Compares two floating-point numbers for near-equality.
     * 
     * This function checks if two floating-point numbers are approximately
     * equal within a specified tolerance.
     * 
     * @param a The first floating-point number.
     * @param b The second floating-point number.
     * @param epsilon The tolerance value (default is 0.0001f).
     * @return true if the numbers are nearly equal, false otherwise.
     */
    static bool nearlyEqual(float a, float b, float epsilon = 0.0001f) {
        return std::fabs(a - b) < epsilon;
    }
};

#endif // COORDINATECONVERTER_H