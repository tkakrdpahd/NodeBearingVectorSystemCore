/**
 * LinerSegment.cpp
 * Implementation of the LinerSegment class
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 9, 2024
 * Last Modified: Nov 11, 2024
 * 
 * Purpose:
 * Implements the LinerSegment class functions for generating B-Spline lines
 * and creating polygon vertices based on Level of Detail (LOD).
 */

#include "LinerSegment.h"
#include <iostream> // For debugging purposes

// Helper function: Component-wise (Hadamard) product of two vectors
Vector3 hadamardProduct(const Vector3& a, const Vector3& b) {
    return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
}

// Constructor
LinerSegment::LinerSegment(const NodeVectorWithBearing& n1, const NodeVectorWithBearing& n2, float lod, float alphaVal)
    : node1(n1), node2(n2), levelOfDetail(lod), alpha(alphaVal), L_min(0.1f), L_max(10.0f) {
    samplingBezierCurve();
}

// Calculate control points based on the equations
void LinerSegment::calculateControlPoints() {
    controlPoints.clear();

    // Equ(9): P0 = N1
    CartesianNodeVector N1 = node1.node.getCartesianNodeVector();
    Vector3 P0 = N1.cartesianCoords;
    controlPoints.push_back(P0);

    // Equ(10): Pi = N1 + Ci, 1 ≤ i ≤ D1
    int D1 = static_cast<int>(node1.bearings.size());
    std::vector<Vector3> C_list_1; // List of Ci for node1

    for (int i = 0; i < D1; ++i) {
        // Calculate Ci using Equations (4) and (5)
        Vector3 Bi = node1.bearings[i].calculateBearingVector(); // Unit bearing vector
        BearingVectorForce Fi = node1.bearings[i].getForce();    // Force vector
        Vector3 Vi = hadamardProduct(Bi, Fi.force);              // Vi = Bi ⊗ Fi
        Vector3 Ci = Vi; // Assuming d_{s,i} = 1
        C_list_1.push_back(Ci);

        Vector3 Pi = P0 + Ci;
        controlPoints.push_back(Pi);
    }

    // Equ(13): Pn = N2
    CartesianNodeVector N2 = node2.node.getCartesianNodeVector();
    Vector3 Pn = N2.cartesianCoords;

    // Equ(11): P_{D1+1} = α(N1 + C_{1,D1}) + (1 - α)(N2 - C_{2,D2})
    Vector3 C_D1 = C_list_1.empty() ? Vector3(0.0f, 0.0f, 0.0f) : C_list_1.back(); // Last Ci of node1
    Vector3 C_D2 = Vector3(0.0f, 0.0f, 0.0f); // Last Ci of node2

    // Calculate Ci for node2's last bearing
    int D2 = static_cast<int>(node2.bearings.size());
    if (D2 > 0) {
        Vector3 Bi = node2.bearings[D2 - 1].calculateBearingVector();
        BearingVectorForce Fi = node2.bearings[D2 - 1].getForce();
        Vector3 Vi = hadamardProduct(Bi, Fi.force);
        C_D2 = Vi; // Assuming d_{s,i} = 1
    }

    Vector3 PD1plus1 = alpha * (P0 + C_D1) + (1.0f - alpha) * (Pn - C_D2);
    controlPoints.push_back(PD1plus1);

    // Equ(12): P_{D1+1+j} = N2 - C_{2,D2 - j + 1}, 1 ≤ j ≤ D2
    std::vector<Vector3> C_list_2; // List of Ci for node2
    for (int j = D2 - 1; j >= 0; --j) {
        // Calculate Ci using Equations (4) and (5)
        Vector3 Bi = node2.bearings[j].calculateBearingVector();
        BearingVectorForce Fi = node2.bearings[j].getForce();
        Vector3 Vi = hadamardProduct(Bi, Fi.force);
        Vector3 Ci = Vi; // Assuming d_{s,i} = 1
        C_list_2.push_back(Ci);

        Vector3 Pi = Pn - Ci;
        controlPoints.push_back(Pi);
    }

    // Equ(13): Pn = N2 (Already added)

    // Reverse the order of control points from node2 bearings to maintain sequence
    std::reverse(controlPoints.begin() + D1 + 2, controlPoints.end());

    // Add Pn to control points
    controlPoints.push_back(Pn);

    // Debug: Print control points
    for (size_t i = 0; i < controlPoints.size(); ++i) {
        Vector3 cp = controlPoints[i];
        std::cout << "Control Point " << i << ": (" << cp.x << ", " << cp.y << ", " << cp.z << ")\n";
    }
}

// Calculate Bezier curve based on control points
void LinerSegment::calculateBezierCurve() {
    sampledPoints.clear();
    int n = static_cast<int>(controlPoints.size()) - 1;
    int sampleCount = static_cast<int>(levelOfDetail);

    for (int i = 0; i <= sampleCount; ++i) {
        float t = static_cast<float>(i) / sampleCount;
        Vector3 Bt(0.0f, 0.0f, 0.0f);
        for (int j = 0; j <= n; ++j) {
            int coeff = binomialCoefficient(n, j);
            float term = coeff * std::pow(1.0f - t, n - j) * std::pow(t, j);
            Bt = Bt + (controlPoints[j] * term);
        }
        sampledPoints.push_back(Bt);
    }
}

// Compute binomial coefficient (n choose k)
int LinerSegment::binomialCoefficient(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k == 0 || k == n) return 1;
    k = std::min(k, n - k); // Take advantage of symmetry
    int c = 1;
    for (int i = 0; i < k; ++i) {
        c = c * (n - i) / (i + 1);
    }
    return c;
}

// Public function to sample the Bezier curve
void LinerSegment::samplingBezierCurve() {
    calculateControlPoints();
    calculateBezierCurve();
}

// Placeholder for SamplingVertex (depends on specific implementation)
void LinerSegment::samplingVertex() {
    // This function would generate polygon vertices based on sampledPoints
    // Implementation depends on how you want to use these vertices
}

// Return LinerSegmentData
LinerSegmentData LinerSegment::returnLinerSegmentData() const {
    LinerSegmentData data;
    data.linerBufferIndex = 0; // Set appropriate value as needed
    data.nodeStart = node1.node;
    data.nodeEnd = node2.node;
    data.levelOfDetail = levelOfDetail;
    data.alpha = alpha;
    return data;
}
