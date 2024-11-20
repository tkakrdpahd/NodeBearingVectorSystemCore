/**
 * LinearSegment.h
 * Linked file LinerSegment.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 9, 2024
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
    int GetIndex() const { return index; }
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
