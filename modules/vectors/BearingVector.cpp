/** 
 * bearingVector.cpp
 * Implementation file for BearingVector
 * Author: Minseok Doo
 * Date: Oct 7, 2024
 * Last Modified: Nov 13, 2024
 */

#include "BearingVector.h"
#include <iostream>

BearingVector::BearingVector(int index, const NodeVector& node, const Vector3& force, const Vector3& vector)
    : index(index), node(node), force(force), vector(vector) {}

BearingVector::~BearingVector() {
    std::cout << "Destroying BearingVector: Node Index: " << index << ", Force: " << force << ", Vector: " << vector << std::endl;
}
