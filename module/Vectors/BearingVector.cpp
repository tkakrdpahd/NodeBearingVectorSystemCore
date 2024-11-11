/* BearingVector.cpp
 * Linked file: BearingVector.h
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 7, 2024
 * Last Modified: Nov 11, 2024
 * 
 * Purpose: Implement functions for the BearingVector class
 */

#include "BearingVector.h"
#include "CoordinateConverter.h"
#include <cmath>

// Constructor implementation
BearingVector::BearingVector(int index, const NodeVector& node, const Vector3& angles, const Vector3& force)
{
    // Extract depth from angles.x
    float depth = angles.x;
    float phi_i = angles.y;
    float theta_i = angles.z;

    // Initialize spherical bearing vector
    sphericalBearing.i = index;
    sphericalBearing.d = depth; // Depth from angles.x
    sphericalBearing.node = node;
    sphericalBearing.angles = angles; // angles.x = depth, angles.y = phi_i, angles.z = theta_i
    sphericalBearing.force.force = force;

    // Initialize Cartesian bearing vector by converting spherical to Cartesian
    // Note: CoordinateConverter expects Vector3(r, theta, phi)
    // Since r is the depth, we use depth as the radius
    Vector3 sphericalCoords(depth, theta_i, phi_i); // r = depth, y = theta, z = phi
    Vector3 cartesianCoords = CoordinateConverter::sphericalToCartesian(sphericalCoords);

    cartesianBearing = CartesianBearingVector(
        index,
        depth,
        cartesianCoords,
        force
    );
}

/**
 * @brief Calculates the Cartesian components of the Bearing Vector (unit vector) based on the spherical angles.
 * 
 * Implements Equation 1:
 * \mathbf{B}_i = 
 * \begin{pmatrix}
 * \sin{\phi_i} \cos{\theta_i} \\
 * \sin{\phi_i} \sin{\theta_i} \\
 * \cos{\phi_i}
 * \end{pmatrix}
 * 
 * @return Vector3 The Cartesian components (x, y, z) of the bearing vector.
 */
Vector3 BearingVector::calculateBearingVector() const {
    float phi = sphericalBearing.angles.y;
    float theta = sphericalBearing.angles.z;

    float x = sin(phi) * cos(theta);
    float y = sin(phi) * sin(theta);
    float z = cos(phi);

    return Vector3(x, y, z);
}

// Function to convert the spherical bearing vector to a Cartesian bearing vector
CartesianBearingVector BearingVector::convertToCartesianBearingVector() const {
    // Use CoordinateConverter to convert spherical to Cartesian
    float depth = sphericalBearing.d;
    float theta_i = sphericalBearing.angles.z;
    float phi_i = sphericalBearing.angles.y;

    Vector3 sphericalCoords(depth, theta_i, phi_i);
    Vector3 cartesianCoords = CoordinateConverter::sphericalToCartesian(sphericalCoords);

    // Initialize and return CartesianBearingVector
    return CartesianBearingVector(
        sphericalBearing.i, 
        depth, 
        cartesianCoords, 
        sphericalBearing.force.force
    );
}

// Function to convert the Cartesian bearing vector back to spherical coordinates (using node vector)
SphericalBearingVectorStruct BearingVector::convertToSphericalBearingVector(const CartesianBearingVector& cartesian, const NodeVector& node) const {
    // Use CoordinateConverter to convert Cartesian to spherical
    Vector3 sphericalCoords = CoordinateConverter::cartesianToSpherical(cartesian.cartesianCoords);

    // Initialize and return SphericalBearingVectorStruct
    SphericalBearingVectorStruct sbv;
    sbv.i = cartesian.i;
    sbv.d = sphericalCoords.x; // depth (radius)
    sbv.node = node;
    sbv.angles.x = sphericalCoords.x;   // depth
    sbv.angles.y = sphericalCoords.z;   // phi
    sbv.angles.z = sphericalCoords.y;   // theta
    sbv.force.force = cartesian.force.force;

    return sbv;
}

// Function to get the force vector components
BearingVectorForce BearingVector::getForce() const {
    return sphericalBearing.force;
}

// Getters for the spherical angles (φ, θ)
float BearingVector::getPhi() const {
    return sphericalBearing.angles.y; // phi_i
}

float BearingVector::getTheta() const {
    return sphericalBearing.angles.z; // theta_i
}

// Get node index and bearing vector depth
int BearingVector::getNodeIndex() const {
    return sphericalBearing.i;
}

float BearingVector::getDepth() const {
    return sphericalBearing.d;
}
