/**
 * BearingVector.h
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 7, 2024
 * Last Modified: Nov 16, 2024
 * 
 * Purpose: Implementation of the BearingVector class methods
 */


#include "Vector3.h"
#include "CoordinateConverter.h"

class BearingVector
{
private:
    int NodeIndex;
    Vector3 Vector;
public:
    BearingVector(/* args */);
    ~BearingVector();
    Vector3 SphericalBearingVector();
    Vector3 CartesianBearingVector();
};
