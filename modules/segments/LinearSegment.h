/**
 * LinearSegment.h
 * 
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
 * @brief LinearSegment 클래스
 * 
 * NodeVector와 BearingVector를 사용하여 B-Spline 곡선을 생성하고,
 * 레벨 오브 디테일(LOD)에 따라 폴리곤 정점을 생성하는 기능을 제공합니다.
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
    int index;
    int LOD;
    NodeVector NodeStart;
    std::vector<BearingVector> BearingVectorStart;
    NodeVector NodeEnd;
    std::vector<BearingVector> BearingVectorEnd;
    std::shared_ptr<std::vector<Vector3>> _linearSegmentCache;
public:
    // 생성자 및 소멸자
    LinearSegment(const NodeVector& start, const std::vector<BearingVector>& bearingStart,
                const NodeVector& end, const std::vector<BearingVector>& bearingEnd);
    ~LinearSegment();

    // 출력 연산자 오버로드 선언
    friend std::ostream& operator<<(std::ostream& os, const LinearSegment& ls);

    // Getter 함수 추가
    const NodeVector& getStartNode() const { return NodeStart; }
    const NodeVector& getEndNode() const { return NodeEnd; }
    std::shared_ptr<std::vector<Vector3>> GetLinearSegmentCache() const;

    // 베지어 곡선의 점 계산 (Equ. 16)
    Vector3 BezierPoint(const std::vector<Vector3>& controlPoints, float t) const;
    // 컨트롤 포인트 계산 (Equ. 17~21)
    std::vector<Vector3> CalculateControlPoints(float alpha) const;
    // 이항 계수 계산 (n choose k)
    float BinomialCoefficient(int n, int k) const;
    // 베지어 곡선의 1차 도함수 계산
    Vector3 BezierFirstDerivative(const std::vector<Vector3>& controlPoints, float t) const;
    // 베지어 곡선의 2차 도함수 계산
    Vector3 BezierSecondDerivative(const std::vector<Vector3>& controlPoints, float t) const;
    // B-Spline 라인 생성
    void CreateBSpline(float alpha, int numSegments);
    // LOD 기반 폴리곤 정점 생성
    std::vector<Vector3> CreatePolygonVertices(int lod) const;
    // 곡률 계산 함수
    float CalculateCurvature(float t) const;
};

#endif // LINEARSEGMENT_H
