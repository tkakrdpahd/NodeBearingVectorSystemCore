/** 
 * NodeVector.h
 * Linked file: NodeVector.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 7, 2024
 * Last Modified: Nov 11, 2024
 * 
 * Purpose of Class:
 * Declare Node Vector
 * 
 * Equations:
 * Equ(1): \vec{N_i} = \left( r_i, \theta_i, \phi_i \right)
 */

#ifndef NODEVECTOR_H
#define NODEVECTOR_H

#include "Vector3.h"
#include "CoordinateConverter.h"

/**
 * @brief Structure representing a Node Vector in spherical coordinates.
 * Uses Vector3 to store spherical coordinates (x = r, y = theta, z = phi).
 */
struct SphericalNodeVector {
    int index;              ///< Index of the node vector
    Vector3 sphericalCoords; ///< Spherical coordinates (r, theta, phi)

    /**
     * @brief Constructor for SphericalNodeVector.
     * 
     * @param idx Index of the node vector.
     * @param coords Spherical coordinates as a Vector3.
     */
    SphericalNodeVector(int idx = 0, const Vector3& coords = Vector3())
        : index(idx), sphericalCoords(coords) {}
};

/**
 * @brief Structure representing a Node Vector in Cartesian coordinates.
 * Uses Vector3 to store Cartesian coordinates (x, y, z).
 */
struct CartesianNodeVector {
    int index;              ///< Index of the node vector
    Vector3 cartesianCoords; ///< Cartesian coordinates (x, y, z)

    /**
     * @brief Constructor for CartesianNodeVector.
     * 
     * @param idx Index of the node vector.
     * @param coords Cartesian coordinates as a Vector3.
     */
    CartesianNodeVector(int idx = 0, const Vector3& coords = Vector3())
        : index(idx), cartesianCoords(coords) {}
};

/**
 * @brief Class representing a Node Vector that can handle both spherical and Cartesian coordinates.
 */
class NodeVector {
private:
    SphericalNodeVector sphericalNode;   ///< Node Vector in spherical coordinates
    CartesianNodeVector cartesianNode;   ///< Node Vector in Cartesian coordinates

public:
    /**
     * @brief Default constructor.
     */
    NodeVector();

    /**
     * @brief Constructor using a SphericalNodeVector.
     * 
     * @param snv SphericalNodeVector to initialize the NodeVector.
     */
    NodeVector(const SphericalNodeVector& snv);

    /**
     * @brief Constructor using a CartesianNodeVector.
     * 
     * @param cnv CartesianNodeVector to initialize the NodeVector.
     */
    NodeVector(const CartesianNodeVector& cnv);

    /**
     * @brief Returns the SphericalNodeVector.
     * 
     * @return SphericalNodeVector The spherical node vector.
     */
    SphericalNodeVector getSphericalNodeVector() const;

    /**
     * @brief Returns the CartesianNodeVector.
     * 
     * @return CartesianNodeVector The Cartesian node vector.
     */
    CartesianNodeVector getCartesianNodeVector() const;

    /**
     * @brief Converts the spherical coordinates to Cartesian coordinates.
     */
    void convertSphericalToCartesian();

    /**
     * @brief Converts the Cartesian coordinates to spherical coordinates.
     */
    void convertCartesianToSpherical();
};

#endif // NODEVECTOR_H
