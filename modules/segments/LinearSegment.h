/**
 * LinearSegment.h
 * Linked file LinerSegment.cpp
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
 */
class LinearSegment
{
private:
    // Parameter need to be save.
    int index;
    int LOD;
    NodeVector NodeStart;
    std::vector<BearingVector> BearingVectorStart;
    NodeVector NodeEnd;
    std::vector<BearingVector> BearingVectorEnd;

    // Cached Sampling data.
    std::shared_ptr<std::vector<Vector3>> _linearSegmentCache;
public:
    // 생성자 및 소멸자
    LinearSegment(const NodeVector& start, const std::vector<BearingVector>& bearingStart,
                const NodeVector& end, const std::vector<BearingVector>& bearingEnd);
    ~LinearSegment();

    // 출력 연산자 오버로드 선언
    friend std::ostream& operator<<(std::ostream& os, const LinearSegment& ls);

    // CRUD Parameters
    int ReadLOD() const { return LOD; }
    int UpdateLOD() const { return LOD; }

    const NodeVector& getStartNode() const { return NodeStart; } // Read StartNode
    const NodeVector& UpdateStartNode() const { return NodeStart; } // Update StartNode

    const NodeVector& getEndNode() const { return NodeEnd; } // Read EndNode
    const NodeVector& UpdateEndNode() const { return NodeEnd; } // Update EndNode

    std::shared_ptr<std::vector<Vector3>> GetLinearSegmentCache() const;

    // Calculation
    Vector3 BezierPoint(const std::vector<Vector3>& controlPoints, float t) const;
    std::vector<Vector3> CalculateControlPoints(float alpha) const;
    float BinomialCoefficient(int n, int k) const;
    Vector3 BezierFirstDerivative(const std::vector<Vector3>& controlPoints, float t) const;
    Vector3 BezierSecondDerivative(const std::vector<Vector3>& controlPoints, float t) const;
    void CreateBSpline(float alpha, int numSegments);
    std::vector<Vector3> CreatePolygonVertices(int lod) const;
    float CalculateCurvature(float t) const;
};

#endif // LINEARSEGMENT_H
