/**
 * LinearSegment.h
 * Linked file LinearSegment.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 9, 2024
 * Last Modified: Nov 20, 2024
 */

#ifndef LINEARSEGMENT_H
#define LINEARSEGMENT_H

#include <vector>
#include <memory>
#include <cmath>
#include <iostream>

#include "Vector3.h"
#include "NodeVector.h"
#include "BearingVector.h"

// Google Test Access
#include <gtest/gtest_prod.h>

/**
 * @brief LinearSegment Class
 * 
 * Purpose: 
 * 1. Create B-Spline line
 * 2. Create Polygon Vertex based on LOD
 * 
 * @param index Index of LinearSegment.
 * @param LOD Level of Detail.
 * @param NodeStart Start point of node vector.
 * @param BearingVectorStart Bearing vectors of starting node vector.
 * @param NodeEnd Endpoint node vector.
 * @param BearingVectorEnd Bearing vectors of Endpoint node vector.
 * @param alpha Parameter for B-Spline calculation.
 * @param numSegments Number of segments for B-Spline sampling.
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
