/**
 * LinearSegment.h
 * Linked file LinearSegment.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 9, 2024
 * Last Modified: Nov 22, 2024
 * 
 * Equations
 * Equ(1): R_i=R_z\left(\theta_i\right)R_y\left(\phi_i\right)
 * Equ(2): R_z\left(\theta_i\right)=\left(\begin{matrix}\cos{\theta_i}&\sin{\theta_i}&0\\\sin{\theta_i}&\cos{\theta_i}&0\\0&0&1\\\end{matrix}\right)
 * Equ(3): R_y\left(\phi_i\right)=\left(\begin{matrix}\cos{\phi_i}&0&\sin{\phi_i}\\0&1&0\\-\sin{\phi_i}&0&\cos{\phi_i}\\\end{matrix}\right)
 * Equ(4): \vec{V_{\mathrm{total},s}}=\sum_{i=1}^{D_s}d_{s,i}\cdot\left(\vec{B_i}\otimes\vec{F_i}\right)
 * Equ(5): \vec{P_{\mathrm{final},s}}=\vec{N_{\mathrm{Cartesian}}}+\vec{V_{\mathrm{total},s}}
 * Equ(6): L_{d,\mathrm{in}}=L_{\mathrm{min}}+\left(L_{\mathrm{max}}-L_{\mathrm{min}}\right)\cdot|\vec{B_{d,\mathrm{in}}}|
 * Equ(7): L_{d,\mathrm{out}}=L_{\mathrm{min}}+\left(L_{\mathrm{max}}-L_{\mathrm{min}}\right)\cdot|\vec{B_{d,\mathrm{out}}}|
 * Equ(8): \vec{B}\left(t\right)=\sum_{i=0}^{n}\binom{n}{i}\left(1-t\right)^{n-i}t^i\vec{P_i},\emsp0\le t\le1
 * Equ(9): \vec{P_0}=\vec{N_1}
 * Equ(10): \vec{P_i}=\vec{N_1}+\vec{C_{1,i}},\emsp1\le i\le D_1
 * Equ(11): \vec{P_{D_1+1}}=\alpha\left(\vec{N_1}+\vec{C_{1,D_1}}\right)+\left(1-\alpha\right)\left(\vec{N_2}-\vec{C_{2,D_2}}\right)
 * Equ(12): \vec{P_{D_1+1+j}}=\vec{N_2}-\vec{C_{2,D_2-j+1}},\emsp1\le j\le D_2
 * Equ(13): \vec{P_n}=\vec{N_2}
 * Equ(14): \kappa\left(t\right)=\frac{|\vec{B^{\prime\prime}}\left(t\right)\times\vec{B^\prime}\left(t\right)|}{|\vec{B^\prime}\left(t\right)|^3}
 */

#ifndef LINEARSEGMENT_H
#define LINEARSEGMENT_H

#include <vector>
#include <memory>
// Google Test Access
#include <gtest/gtest_prod.h>

#include "Vector3.h"
#include "NodeVector.h"
#include "BearingVector.h"

/**
 * @brief LinearSegment class
 * 
 * Expected input [int lod, std::vector<NodeVector> NodeVector StartNode, NodeVector EndNode, std::vector<BearingVector> BearingVector StartNodeBearing, EndNodeBearing]
 */
class LinearSegment
{
private:
    // Parameters to be saved.
    int index;
    int LOD;
    NodeVector NodeStart;
    std::vector<BearingVector> BearingVectorStart;
    NodeVector NodeEnd;
    std::vector<BearingVector> BearingVectorEnd;

    // New Parameters for automatic calculations
    float alpha;
    int numSegments;

    // Cached Sampling data.
    std::shared_ptr<std::vector<Vector3>> _linearSegmentCache;

    // Calculation
    Vector3 BezierPoint(const std::vector<Vector3>& controlPoints, float t) const;
    std::vector<Vector3> CalculateControlPoints(float alpha) const;
    float BinomialCoefficient(int n, int k) const;
    Vector3 BezierFirstDerivative(const std::vector<Vector3>& controlPoints, float t) const;
    Vector3 BezierSecondDerivative(const std::vector<Vector3>& controlPoints, float t) const;
    void CreateBSpline(); // Modified to use member variables
    std::vector<Vector3> CreatePolygonVertices(int lod) const;
    float CalculateCurvature(float t) const;

    // FRIEND_TEST 선언 추가
    FRIEND_TEST(LinearSegmentTest, ControlPointsTest);
    FRIEND_TEST(LinearSegmentTest, BSplineCreationTest);
    FRIEND_TEST(LinearSegmentTest, PolygonVerticesTest);
    FRIEND_TEST(LinearSegmentTest, CurvatureTest);
    FRIEND_TEST(LinearSegmentTest, AutomaticBSplineOnAlphaUpdate);
    FRIEND_TEST(LinearSegmentTest, AutomaticBSplineOnNumSegmentsUpdate);
    FRIEND_TEST(LinearSegmentTest, AutomaticBSplineOnStartNodeUpdate);
    FRIEND_TEST(LinearSegmentTest, AutomaticBSplineOnEndNodeUpdate);

public:
    // Constructors and Destructors
    LinearSegment(const NodeVector& start, const std::vector<BearingVector>& bearingStart,
                const NodeVector& end, const std::vector<BearingVector>& bearingEnd,
                float alpha = 0.5f, int numSegments = 100);
    ~LinearSegment();

    // Output Operator Overload Declaration
    friend std::ostream& operator<<(std::ostream& os, const LinearSegment& ls);

    // Getter Methods
    int ReadLOD() const { return LOD; }
    const NodeVector& getStartNode() const { return NodeStart; } // Read StartNode
    const NodeVector& getEndNode() const { return NodeEnd; } // Read EndNode

    // Setter Methods
    void SetLOD(int newLOD);
    void SetStartNode(const NodeVector& newStart);
    void SetEndNode(const NodeVector& newEnd);
    void SetAlpha(float newAlpha);
    void SetNumSegments(int newNumSegments);

    // Access Cached Data
    std::shared_ptr<std::vector<Vector3>> GetLinearSegmentCache() const;
};

#endif // LINEARSEGMENT_H