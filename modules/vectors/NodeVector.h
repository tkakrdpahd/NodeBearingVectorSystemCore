// NodeVector.h

#ifndef NODEVECTOR_H
#define NODEVECTOR_H

#include "Vector3.h"
#include "CoordinateConverter.h"

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

    // (int, Vector3) 생성자 추가
    NodeVector(int nodeId, const Vector3& vec) : Index(nodeId), Vector(vec) {}
};

#endif // NODEVECTOR_H
