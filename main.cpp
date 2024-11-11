/**
 * main.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 13, 2024
 * Last Modified: Nov 11, 2024
 */

#include <iostream>
#include <cmath>
#include "CoordinateConverter.h"
#include "Vector3.h"
#include "NodeVector.h"

int main() {
    // Create a SphericalNodeVector
    int index = 1;
    Vector3 sphericalCoords(1.0f, M_PI / 4, M_PI / 4); // r=1, theta=45°, phi=45°
    SphericalNodeVector snv(index, sphericalCoords);

    // Initialize NodeVector with SphericalNodeVector
    NodeVector node(snv);

    // Get the Cartesian coordinates
    CartesianNodeVector cnv = node.getCartesianNodeVector();
    std::cout << "Cartesian Coordinates: (" << cnv.cartesianCoords.x << ", "
              << cnv.cartesianCoords.y << ", " << cnv.cartesianCoords.z << ")\n";

    // Similarly, you can initialize with CartesianNodeVector
    Vector3 cartesianCoords(1.0f, 1.0f, 1.0f);
    CartesianNodeVector cnv2(index, cartesianCoords);

    NodeVector node2(cnv2);

    // Get the Spherical coordinates
    SphericalNodeVector snv2 = node2.getSphericalNodeVector();
    std::cout << "Spherical Coordinates: (r=" << snv2.sphericalCoords.x
              << ", theta=" << snv2.sphericalCoords.y
              << ", phi=" << snv2.sphericalCoords.z << ")\n";

    return 0;
}
