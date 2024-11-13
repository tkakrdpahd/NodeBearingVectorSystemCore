/** 
 * bearingVector.h
 * Linked file: bearingVector.cpp
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

#include "Vector3.h"
#include "NodeVector.h"
#include <ostream>

class BearingVector {
private:
    NodeVector node;
public:
    int index;
    Vector3 force;
    Vector3 vector;

    BearingVector(int idx, const NodeVector& nd, const Vector3& frc, const Vector3& vec);
    ~BearingVector();

    friend std::ostream& operator<<(std::ostream& os, const BearingVector& bearing) {
        os << "NodeIndex: " << bearing.index << ", Force: " << bearing.force << ", Vector: " << bearing.vector;
        return os;
    }
};

#endif // BEARINGVECTOR_H