/**
 * BearingVector.h
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 7, 2024
 * Last Modified: Nov 16, 2024
 * 
 * Purpose: Implementation of the BearingVector class methods
 * 
 * Equations
 * Equ(1): (B_i ) ⃗=(■(sin⁡ϕ_i cos⁡θ_i@sin⁡ϕ_i sin⁡θ_i@cos⁡ϕ_i ))
 * Equ(2): (B_(i,d) ) ⃗=(B_(i,d,x),B_(i,d,y),B_(i,d,z) )
 * Equ(3): (F_i ) ⃗=F_(x_i ) x ̂+F_(y_i ) y ̂+F_(z_i ) z ̂
 * Equ(4): R_i=R_z (θ_i ) R_y (ϕ_i )
 * Equ(5): R_z (θ_i )=(■(cos⁡θ_i & -sin⁡θ_i & 0@sin⁡θ_i & cos⁡θ_i & 0@0 & 0 & 1))
 * Equ(6): R_y (ϕ_i )=(■(cos⁡ϕ_i & 0 & sin⁡ϕ_i@0 & 1 & 0@-sin⁡ϕ_i & 0 & cos⁡ϕ_i ))
 */

#ifndef BEARINGVECTOR_H
#define BEARINGVECTOR_H

#include "Vector3.h"
#include "NodeVector.h"
#include "CoordinateConverter.h"

/**
 * @brief Bearing Vector
 * 
 * @param NodeVector Parent Node Vector
 * @param Force Bearing Vector Force; (x, y, z)
 * @param Vector Bearing Vector location; (x, y, z), (d_i, theta_i, phi_i)
 */
struct BearingVector
{
    NodeVector Node;
    Vector3 Force;
    Vector3 Vector;

    // 기본 생성자
    // NodeVector을 기본값으로 초기화
    BearingVector() : Node(0, Vector3()), Force(), Vector() {}

    // 매개변수 생성자
    BearingVector(const NodeVector& node, const Vector3& force, const Vector3& vec) 
        : Node(node), Force(force), Vector(vec) {}
};

#endif // BEARINGVECTOR_H
