/**
 * main.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 13, 2024
 * Last Modified: Nov 11, 2024
 */

#include <iostream>
#include <cmath>
#include <vector>

#include "Vector3.h"
#include "CoordinateConverter.h"
#include "NodeVector.h"
#include "BearingVector.h"
#include "LinerSegment.h"

int main() {
    // Constants for degrees to radians conversion
    const float DEG_TO_RAD = M_PI / 180.0f;

    // **Step 1: Create NodeVectors**

    // Node 1 at position (1, 1, 1) in Cartesian coordinates
    Vector3 node1CartesianCoords(1.0f, 1.0f, 1.0f);
    CartesianNodeVector cnv1(1, node1CartesianCoords);
    NodeVector node1(cnv1);

    // Node 2 at position (5, 5, 5) in Cartesian coordinates
    Vector3 node2CartesianCoords(5.0f, 5.0f, 5.0f);
    CartesianNodeVector cnv2(2, node2CartesianCoords);
    NodeVector node2(cnv2);

    // **Step 2: Create BearingVectors for each Node**

    // BearingVector for Node 1
    int bearingIndex1 = 1;
    // Angles vector: angles.x = depth, angles.y = phi_i, angles.z = theta_i
    Vector3 bearingAngles1(1.0f, 45.0f * DEG_TO_RAD, 30.0f * DEG_TO_RAD); // depth, phi, theta
    Vector3 bearingForce1(2.0f, 2.0f, 2.0f);
    BearingVector bearingVector1(bearingIndex1, node1, bearingAngles1, bearingForce1);

    // BearingVector for Node 2
    int bearingIndex2 = 2;
    Vector3 bearingAngles2(1.0f, 60.0f * DEG_TO_RAD, 45.0f * DEG_TO_RAD);
    Vector3 bearingForce2(3.0f, 3.0f, 3.0f);
    BearingVector bearingVector2(bearingIndex2, node2, bearingAngles2, bearingForce2);

    // **Step 3: Create NodeVectorWithBearing instances**

    // Node 1 with its bearings
    NodeVectorWithBearing nodeWithBearing1;
    nodeWithBearing1.node = node1;
    nodeWithBearing1.bearings.push_back(bearingVector1);

    // Node 2 with its bearings
    NodeVectorWithBearing nodeWithBearing2;
    nodeWithBearing2.node = node2;
    nodeWithBearing2.bearings.push_back(bearingVector2);

    // **Step 4: Create a LinerSegment**

    float lod = 50.0f;    // Level of Detail
    float alphaVal = 0.5f; // Blending factor

    LinerSegment linerSegment(nodeWithBearing1, nodeWithBearing2, lod, alphaVal);

    // **Step 5: Access and Output Sampled Points**

    const std::vector<Vector3>& sampledPoints = linerSegment.getSampledPoints();

    std::cout << "Sampled Points along the Bezier Curve:\n";
    for (size_t i = 0; i < sampledPoints.size(); ++i) {
        const Vector3& pt = sampledPoints[i];
        std::cout << "Point " << i << ": (" << pt.x << ", " << pt.y << ", " << pt.z << ")\n";
    }

    // **Optional: Output Control Points**

    const std::vector<Vector3>& controlPoints = linerSegment.getControlPoints();

    std::cout << "\nControl Points for the Bezier Curve:\n";
    for (size_t i = 0; i < controlPoints.size(); ++i) {
        const Vector3& cp = controlPoints[i];
        std::cout << "Control Point " << i << ": (" << cp.x << ", " << cp.y << ", " << cp.z << ")\n";
    }

    // **Step 6: Retrieve and Output LinerSegmentData**

    LinerSegmentData segmentData = linerSegment.returnLinerSegmentData();
    std::cout << "\nLinerSegment Data:\n";
    std::cout << "Level of Detail: " << segmentData.levelOfDetail << "\n";
    std::cout << "Alpha: " << segmentData.alpha << "\n";

    return 0;
}
