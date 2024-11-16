/** 
 * NodeVector.h
 * Linked file: NodeVector.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 7, 2024
 * Last Modified: Nov 13, 2024
 * 
 * Purpose of Class:
 * Declare Node Vector
 * 
 * Equations:
 * Equ(1): \vec{N_i} = \left( r_i, \theta_i, \phi_i \right)
 */

#ifndef NODEVECTOR_H
#define NODEVECTOR_H

#include <iostream>
#include "Vector3.h"

class NodeVector {
public:
    int index;
    Vector3 vector;

    NodeVector(int index, const Vector3& vector) : index(index), vector(vector) {}
    
    // << 연산자 오버로딩
    friend std::ostream& operator<<(std::ostream& os, const NodeVector& node) {
        os << "Index: " << node.index << ", Vector: " << node.vector;
        return os;
    }
};

#endif // NODEVECTOR_H
