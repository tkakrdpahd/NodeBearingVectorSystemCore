/**
 * bearingVector.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 7, 2024
 * Last Modified: Nov 16, 2024
 * 
 * Purpose: Implementation of the BearingVector class methods
 */

#include "BearingVector.h"
#include <iostream>

// Constructor
BearingVector::BearingVector(int idx, const NodeVector& nd, const Vector3& frc, const Vector3& vec)
    : node(nd), index(idx), force(frc), vector(vec) {
    std::cout << "BearingVector constructed with index " << index << "." << std::endl;
}

// Destructor
BearingVector::~BearingVector() {
    std::cout << "BearingVector with index " << index << " is being destroyed." << std::endl;
}

// Getter Method
const NodeVector& BearingVector::getNodeVector() const {
    return node;
}
