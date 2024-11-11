/**
 * NodeVector.cpp
 * Linked file: NodeVector.h
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 7, 2024
 * Last Modified: Nov 11, 2024
 * 
 * Purpose of Class:
 * Implement Node Vector methods
 */

#include <cmath>                 // For mathematical functions
#include "NodeVector.h"
#include "CoordinateConverter.h" // Include CoordinateConverter
#include "Vector3.h"

/**
 * @brief Default constructor.
 */
NodeVector::NodeVector()
    : sphericalNode(), cartesianNode() {}

/**
 * @brief Constructor using a SphericalNodeVector.
 * Initializes the NodeVector and converts to Cartesian coordinates.
 * 
 * @param snv SphericalNodeVector to initialize the NodeVector.
 */
NodeVector::NodeVector(const SphericalNodeVector& snv)
    : sphericalNode(snv) {
    convertSphericalToCartesian();  // Convert to Cartesian coordinates upon creation
}

/**
 * @brief Constructor using a CartesianNodeVector.
 * Initializes the NodeVector and converts to spherical coordinates.
 * 
 * @param cnv CartesianNodeVector to initialize the NodeVector.
 */
NodeVector::NodeVector(const CartesianNodeVector& cnv)
    : cartesianNode(cnv) {
    convertCartesianToSpherical();  // Convert to spherical coordinates upon creation
}

/**
 * @brief Returns the SphericalNodeVector.
 * 
 * @return SphericalNodeVector The spherical node vector.
 */
SphericalNodeVector NodeVector::getSphericalNodeVector() const {
    return sphericalNode;
}

/**
 * @brief Returns the CartesianNodeVector.
 * 
 * @return CartesianNodeVector The Cartesian node vector.
 */
CartesianNodeVector NodeVector::getCartesianNodeVector() const {
    return cartesianNode;
}

/**
 * @brief Converts the spherical coordinates to Cartesian coordinates.
 */
void NodeVector::convertSphericalToCartesian() {
    // Extract r, theta, phi from the sphericalCoords Vector3
    float r = sphericalNode.sphericalCoords.x;
    float theta = sphericalNode.sphericalCoords.y; // Azimuthal angle (radians)
    float phi = sphericalNode.sphericalCoords.z;   // Polar angle (radians)

    // Create a Vector3 for spherical coordinates
    Vector3 sphericalCoords(r, theta, phi);

    // Use CoordinateConverter to convert to Cartesian coordinates
    Vector3 cartesianCoords = CoordinateConverter::sphericalToCartesian(sphericalCoords);

    // Update the CartesianNodeVector
    cartesianNode.index = sphericalNode.index;
    cartesianNode.cartesianCoords = cartesianCoords;
}

/**
 * @brief Converts the Cartesian coordinates to spherical coordinates.
 */
void NodeVector::convertCartesianToSpherical() {
    // Extract x, y, z from the cartesianCoords Vector3
    float x = cartesianNode.cartesianCoords.x;
    float y = cartesianNode.cartesianCoords.y;
    float z = cartesianNode.cartesianCoords.z;

    // Create a Vector3 for Cartesian coordinates
    Vector3 cartesianCoords(x, y, z);

    // Use CoordinateConverter to convert to spherical coordinates
    Vector3 sphericalCoords = CoordinateConverter::cartesianToSpherical(cartesianCoords);

    // Update the SphericalNodeVector
    sphericalNode.index = cartesianNode.index;
    sphericalNode.sphericalCoords = sphericalCoords;
}
