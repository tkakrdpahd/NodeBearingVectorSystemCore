/**
 * main.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 13, 2024
 * Last Modified: Nov 11, 2024
 */

#include <iostream>
#include <cmath>
#include "CoordinateConverter.h"
#include "Vector3.h"  // Include Vector3.h

int main() {
    // Constants for degrees to radians conversion
    const float DEG_TO_RAD = M_PI / 180.0f;

    // Test case 1: Convert spherical to Cartesian coordinates
    Vector3 spherical(1.0f, 45.0f * DEG_TO_RAD, 45.0f * DEG_TO_RAD);  // r = 1, theta = 45°, phi = 45°
    Vector3 cartesian = CoordinateConverter::sphericalToCartesian(spherical);

    std::cout << "Spherical to Cartesian:" << std::endl;
    std::cout << "Input Spherical (r=1, theta=45°, phi=45°):" << std::endl;
    std::cout << "Converted Cartesian (x, y, z): (" << cartesian.x << ", " << cartesian.y << ", " << cartesian.z << ")\n";

    // Expected Cartesian values (approximately)
    std::cout << "Expected Cartesian (x, y, z): (0.5, 0.5, 0.7071)\n";
    std::cout << "Conversion successful: "
              << (CoordinateConverter::nearlyEqual(cartesian.x, 0.5f) &&
                  CoordinateConverter::nearlyEqual(cartesian.y, 0.5f) &&
                  CoordinateConverter::nearlyEqual(cartesian.z, 0.7071f))
              << "\n\n";

    // Test case 2: Convert Cartesian to spherical coordinates
    Vector3 cartesian2(1.0f, 1.0f, 1.0f);
    Vector3 spherical2 = CoordinateConverter::cartesianToSpherical(cartesian2);

    std::cout << "Cartesian to Spherical:" << std::endl;
    std::cout << "Input Cartesian (x=1, y=1, z=1):" << std::endl;
    std::cout << "Converted Spherical (r, theta, phi): (" << spherical2.x << ", " << spherical2.y << ", " << spherical2.z << ")\n";

    // Expected Spherical values (approximately)
    std::cout << "Expected Spherical (r, theta, phi): (1.732, 0.7854, 0.9553)\n";
    std::cout << "Conversion successful: "
              << (CoordinateConverter::nearlyEqual(spherical2.x, 1.732f) &&
                  CoordinateConverter::nearlyEqual(spherical2.y, 0.7854f) &&
                  CoordinateConverter::nearlyEqual(spherical2.z, 0.9553f))
              << "\n";

    return 0;
}
