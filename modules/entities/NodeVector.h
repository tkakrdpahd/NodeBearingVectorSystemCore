/**
 * NodeVector.h
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 7, 2024
 * Last Modified: Nov 16, 2024
 * 
 */

#ifndef NODEVECTOR_H
#define NODEVECTOR_H

#include "Vector3.h"

/**
 * @brief Node Vector
 * 
 * @param Index Node Vector index
 * @param Vector Node Vector location; (x, y, z), (r_i, theta_i, phi_i)
 */
struct NodeVector
{
    int Index;
    Vector3 Vector;

    // (int, Vector3) constructor
    NodeVector(int nodeId, const Vector3& vec) : Index(nodeId), Vector(vec) {}

    // 출력 연산자 오버로드
    friend std::ostream& operator<<(std::ostream& os, const NodeVector& nv) {
        os << "NodeVector(Index: " << nv.Index << ", Vector: " << nv.Vector << ")";
        return os;
    }
};

#endif // NODEVECTOR_H