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

#include "Vector3.h"
#include "CoordinateConverter.h"

class NodeVector
{
private:
    int Index;
    Vector3 Vector;
public:
    NodeVector(/* args */);
    ~NodeVector();
    Vector3 SphericalNodeVector();
    Vector3 CartesianNodeVector();
};
