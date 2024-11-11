/**
 * BearingVector.h
 * Linked file: BearingVector.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 7, 2024
 * Last Modified: Nov 11, 2024
 * 
 * Purpose: Define functions for the BearingVector class
 * 
 * Equations:
 * Equation 1:
 * \mathbf{B}_i = 
 * \begin{pmatrix}
 * \sin{\phi_i} \cos{\theta_i} \\
 * \sin{\phi_i} \sin{\theta_i} \\
 * \cos{\phi_i}
 * \end{pmatrix}
 * 
 * Equation 2:
 * \mathbf{B}_{i,d} = (B_{i,d,x}, B_{i,d,y}, B_{i,d,z})
 * 
 * Equation 3:
 * \mathbf{F}_i = F_{x_i} \, \hat{x} + F_{y_i} \, \hat{y} + F_{z_i} \, \hat{z}
 * 
 * Equation 4:
 * R_i = R_z(\theta_i) R_y(\phi_i)
 * 
 * Equation 5:
 * R_z(\theta_i) = 
 * \begin{pmatrix}
 * \cos{\theta_i} & -\sin{\theta_i} & 0 \\
 * \sin{\theta_i} & \cos{\theta_i} & 0 \\
 * 0 & 0 & 1
 * \end{pmatrix}
 * 
 * Equation 6:
 * R_y(\phi_i) = 
 * \begin{pmatrix}
 * \cos{\phi_i} & 0 & \sin{\phi_i} \\
 * 0 & 1 & 0 \\
 * -\sin{\phi_i} & 0 & \cos{\phi_i}
 * \end{pmatrix}
 * 
 * Equation 7:
 * \mathbf{V}_{\text{total}, s} = \sum_{i=1}^{D_s} d_{s,i} \cdot \left( \mathbf{B}_i \otimes \mathbf{F}_i \right)
 */

#ifndef BEARINGVECTOR_H
#define BEARINGVECTOR_H

#include <cmath>
#include "Vector3.h"
#include "CoordinateConverter.h"
#include "NodeVector.h"

/**
 * @brief Structure to represent the force vector in BearingVector.
 */
struct BearingVectorForce { 
    Vector3 force; ///< Force vector components (Fx, Fy, Fz)
};

/**
 * @brief Structure to hold spherical bearing vector data using Vector3.
 */
struct SphericalBearingVectorStruct {
    int i;          ///< Node vector index
    float d;        ///< Bearing vector depth (extracted from angles.x)
    NodeVector node; ///< Node vector
    Vector3 angles; ///< Angles Vector3 where x = depth, y = phi_i, z = theta_i
    BearingVectorForce force;  ///< Force vector (Fx, Fy, Fz)
};

/**
 * @brief Structure to hold Cartesian bearing vector data.
 */
struct CartesianBearingVector {
    int i;          ///< Node vector index
    float d;        ///< Bearing vector depth
    Vector3 cartesianCoords; ///< Cartesian coordinates (x, y, z)
    BearingVectorForce force; ///< Force vector in Cartesian coordinates

    /**
     * @brief Constructor to initialize the Cartesian Bearing Vector.
     * 
     * @param index Node vector index.
     * @param depth Bearing vector depth.
     * @param coords Cartesian coordinates.
     * @param forceVec Force vector components.
     */
    CartesianBearingVector(int index = 0, float depth = 0.0f, const Vector3& coords = Vector3(), const Vector3& forceVec = Vector3())
        : i(index), d(depth), cartesianCoords(coords), force{forceVec} {}
};

/**
 * @brief BearingVector class.
 *        Manages both spherical and Cartesian forms of the Bearing Vector.
 */
class BearingVector {
private:
    SphericalBearingVectorStruct sphericalBearing; ///< Spherical bearing vector data
    CartesianBearingVector cartesianBearing;       ///< Cartesian bearing vector data

public:
    /**
     * @brief Constructor for BearingVector.
     * 
     * @param index Node vector index.
     * @param node NodeVector instance.
     * @param angles Vector3 containing depth (angles.x), phi_i (angles.y), theta_i (angles.z).
     * @param force Vector3 containing force components (Fx, Fy, Fz).
     */
    BearingVector(int index, const NodeVector& node, const Vector3& angles, const Vector3& force);

    /**
     * @brief Calculates the Cartesian components of the Bearing Vector (unit vector) based on the spherical angles.
     * 
     * @return Vector3 The Cartesian components (x, y, z) of the bearing vector.
     */
    Vector3 calculateBearingVector() const;

    /**
     * @brief Converts the spherical bearing vector to a Cartesian bearing vector.
     * 
     * @return CartesianBearingVector Converted Cartesian bearing vector.
     */
    CartesianBearingVector convertToCartesianBearingVector() const;

    /**
     * @brief Converts the Cartesian bearing vector back to spherical coordinates.
     * 
     * @param cartesian Cartesian bearing vector to convert.
     * @param node NodeVector instance for reference.
     * @return SphericalBearingVectorStruct Converted spherical bearing vector.
     */
    SphericalBearingVectorStruct convertToSphericalBearingVector(const CartesianBearingVector& cartesian, const NodeVector& node) const;

    /**
     * @brief Gets the force vector components.
     * 
     * @return BearingVectorForce Force vector.
     */
    BearingVectorForce getForce() const;

    /**
     * @brief Getter for the polar angle (φ).
     * 
     * @return float Polar angle.
     */
    float getPhi() const;

    /**
     * @brief Getter for the azimuthal angle (θ).
     * 
     * @return float Azimuthal angle.
     */
    float getTheta() const;

    /**
     * @brief Getter for the node index.
     * 
     * @return int Node index.
     */
    int getNodeIndex() const;

    /**
     * @brief Getter for the bearing vector depth.
     * 
     * @return float Bearing vector depth.
     */
    float getDepth() const;
};

#endif // BEARINGVECTOR_H
