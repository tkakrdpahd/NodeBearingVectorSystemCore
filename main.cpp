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
#include "Vector3.h"
#include "NodeVector.h"
#include "BearingVector.h"

int main() {
    // Constants for degrees to radians conversion
    const float DEG_TO_RAD = M_PI / 180.0f;

    // Create a NodeVector
    int nodeIndex = 1;
    // For the NodeVector, we need to provide spherical coordinates
    // Let's assume the node is at depth = 1.0, phi = 45°, theta = 45°
    Vector3 nodeSphericalCoords(1.0f, 45.0f * DEG_TO_RAD, 45.0f * DEG_TO_RAD); // depth, phi, theta
    SphericalNodeVector snv(nodeIndex, nodeSphericalCoords);
    NodeVector nodeVector(snv);

    // Get the Cartesian coordinates
    CartesianNodeVector cnv = nodeVector.getCartesianNodeVector();
    std::cout << "Cartesian Node Vector Coordinates: (" << cnv.cartesianCoords.x << ", "
              << cnv.cartesianCoords.y << ", " << cnv.cartesianCoords.z << ")\n";

    // Create a BearingVector
    int bearingIndex = 1;
    // Angles vector: angles.x = depth, angles.y = phi_i, angles.z = theta_i
    // Let's set depth = 0.5, phi = 30°, theta = 60°
    Vector3 bearingAngles(0.5f, 30.0f * DEG_TO_RAD, 60.0f * DEG_TO_RAD);
    // Force vector components
    Vector3 bearingForce(10.0f, 5.0f, 2.0f);

    BearingVector bearingVector(bearingIndex, nodeVector, bearingAngles, bearingForce);

    // Test calculateBearingVector()
    Vector3 bearingComponents = bearingVector.calculateBearingVector();
    std::cout << "Bearing Vector Components (unit vector): (" << bearingComponents.x << ", "
              << bearingComponents.y << ", " << bearingComponents.z << ")\n";

    // Test convertToCartesianBearingVector()
    CartesianBearingVector cartesianBearing = bearingVector.convertToCartesianBearingVector();
    std::cout << "\nCartesian Bearing Vector:\n";
    std::cout << "Index: " << cartesianBearing.i << "\n";
    std::cout << "Depth: " << cartesianBearing.d << "\n";
    std::cout << "Coordinates: (" << cartesianBearing.cartesianCoords.x << ", "
              << cartesianBearing.cartesianCoords.y << ", " << cartesianBearing.cartesianCoords.z << ")\n";
    std::cout << "Force: (" << cartesianBearing.force.force.x << ", "
              << cartesianBearing.force.force.y << ", " << cartesianBearing.force.force.z << ")\n";

    // Test getForce()
    BearingVectorForce force = bearingVector.getForce();
    std::cout << "\nBearing Vector Force: (" << force.force.x << ", " << force.force.y << ", " << force.force.z << ")\n";

    // Test getPhi(), getTheta(), getDepth()
    std::cout << "\nBearing Vector Phi (radians): " << bearingVector.getPhi() << "\n";
    std::cout << "Bearing Vector Theta (radians): " << bearingVector.getTheta() << "\n";
    std::cout << "Bearing Vector Depth: " << bearingVector.getDepth() << "\n";

    // Optionally, test convertToSphericalBearingVector()
    SphericalBearingVectorStruct sphericalBearing = bearingVector.convertToSphericalBearingVector(cartesianBearing, nodeVector);
    std::cout << "\nSpherical Bearing Vector (from conversion):\n";
    std::cout << "Index: " << sphericalBearing.i << "\n";
    std::cout << "Depth: " << sphericalBearing.d << "\n";
    std::cout << "Angles (depth, phi, theta): (" << sphericalBearing.angles.x << ", "
              << sphericalBearing.angles.y << ", " << sphericalBearing.angles.z << ")\n";
    std::cout << "Force: (" << sphericalBearing.force.force.x << ", "
              << sphericalBearing.force.force.y << ", " << sphericalBearing.force.force.z << ")\n";

    return 0;
}
