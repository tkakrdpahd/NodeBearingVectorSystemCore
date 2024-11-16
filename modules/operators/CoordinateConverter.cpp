/**
 * CoordinateConverter.cpp
 */

#include "CoordinateConverter.h"

// Converts spherical coordinates to Cartesian coordinates
Vector3 CoordinateConverter::sphericalToCartesian(const Vector3& sv) {
    float r = sv.x;
    float theta = sv.y;
    float phi = sv.z;

    float x = r * std::sin(phi) * std::cos(theta);
    float y = r * std::sin(phi) * std::sin(theta);
    float z = r * std::cos(phi);

    return Vector3(x, y, z);
}

// Converts Cartesian coordinates to spherical coordinates
Vector3 CoordinateConverter::cartesianToSpherical(const Vector3& cv) {
    float x = cv.x;
    float y = cv.y;
    float z = cv.z;

    float r = std::sqrt(x * x + y * y + z * z);
    float theta = std::atan2(y, x);
    float phi = std::acos(z / r);

    return Vector3(r, theta, phi);
}
