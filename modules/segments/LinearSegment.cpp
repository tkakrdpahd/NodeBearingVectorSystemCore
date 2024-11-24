// LinearSegment.cpp

#include "LinearSegment.h"
#include <cmath>
#include <iostream>

// Constructor
LinearSegment::LinearSegment(const Vertex& start, const Vertex& end, float alpha, int numSegments)
    : index(0), // Initialize index (modify as needed)
      LOD(1),    // Initialize LOD (default to 1)
      startVertex(start),
      endVertex(end),
      alpha(alpha),
      numSegments(numSegments),
      _linearSegmentCache(std::make_shared<std::vector<Vector3>>())
{
    // Automatically perform calculations upon creation
    CreateBSpline();
}

// Destructor
LinearSegment::~LinearSegment()
{
    // Cleanup code if necessary
}

// Binomial Coefficient Calculation
float LinearSegment::BinomialCoefficient(int n, int k) const
{
    if (k < 0 || k > n)
        return 0.0f;
    if (k == 0 || k == n)
        return 1.0f;
    if (k > n - k)
        k = n - k;
    float result = 1.0f;
    for (int i = 1; i <= k; ++i)
    {
        result *= (n - (k - i)) / static_cast<float>(i);
    }
    return result;
}

// Bezier Curve Point Calculation
Vector3 LinearSegment::BezierPoint(const std::vector<Vector3>& controlPoints, float t) const
{
    int n = static_cast<int>(controlPoints.size()) - 1;
    Vector3 point(0.0f, 0.0f, 0.0f);
    for (int i = 0; i <= n; ++i)
    {
        float binomial = BinomialCoefficient(n, i);
        float term = binomial * powf(1.0f - t, n - i) * powf(t, i);
        point = point + (controlPoints[i] * term);
    }
    return point;
}

// Bezier Curve First Derivative
Vector3 LinearSegment::BezierFirstDerivative(const std::vector<Vector3>& controlPoints, float t) const
{
    int n = static_cast<int>(controlPoints.size()) - 1;
    Vector3 derivative(0.0f, 0.0f, 0.0f);
    for (int i = 0; i < n; ++i)
    {
        Vector3 diff = controlPoints[i + 1] - controlPoints[i];
        float binomial = BinomialCoefficient(n - 1, i);
        float term = binomial * powf(1.0f - t, (n - 1) - i) * powf(t, i);
        derivative = derivative + (diff * (term * n));
    }
    return derivative;
}

// Bezier Curve Second Derivative
Vector3 LinearSegment::BezierSecondDerivative(const std::vector<Vector3>& controlPoints, float t) const
{
    int n = static_cast<int>(controlPoints.size()) - 1;
    if (n < 2)
        return Vector3(0.0f, 0.0f, 0.0f); // Second derivative undefined

    Vector3 secondDerivative(0.0f, 0.0f, 0.0f);
    for (int i = 0; i < n - 1; ++i)
    {
        Vector3 diff = controlPoints[i + 2] - 2.0f * controlPoints[i + 1] + controlPoints[i];
        float binomial = BinomialCoefficient(n - 2, i);
        float term = binomial * powf(1.0f - t, (n - 2) - i) * powf(t, i);
        secondDerivative = secondDerivative + (diff * (term * n * (n - 1)));
    }
    return secondDerivative;
}

// Calculate Control Points
std::vector<Vector3> LinearSegment::CalculateControlPoints(float alpha) const
{
    std::vector<Vector3> controlPoints;

    // P0 = StartVertex's NodeVector (Equ. 17)
    controlPoints.push_back(startVertex.ReadNodeVector().Vector);
    std::cout << "P0: " << controlPoints.back() << std::endl;

    // P1 ~ P_D1 (Equ. 18)
    const std::vector<BearingVector>& startBearings = startVertex.ReadBearingVectorList();
    std::vector<Vector3> C_start;
    for (const auto& bearing : startBearings)
    {
        Vector3 C_i = bearing.Vector * bearing.Force.magnitude(); // Assuming Force magnitude as scalar
        C_start.push_back(C_i);
        Vector3 Pi = startVertex.ReadNodeVector().Vector + C_i;
        controlPoints.push_back(Pi);
        std::cout << "Pi: " << Pi << std::endl;
    }

    // P_(D1+1) = alpha * (N1 + C_(1,D1)) + (1 - alpha) * (N2 - C_(2,D2)) (Equ. 19)
    Vector3 C_end;
    const std::vector<BearingVector>& endBearings = endVertex.ReadBearingVectorList();
    if (!endBearings.empty())
    {
        const auto& lastBearingEnd = endBearings.back();
        C_end = lastBearingEnd.Vector * lastBearingEnd.Force.magnitude(); // Assuming Force magnitude as scalar
    }
    else
    {
        C_end = Vector3(0.0f, 0.0f, 0.0f);
    }

    Vector3 P_D1_plus_1;
    if (!C_start.empty())
    {
        P_D1_plus_1 = (startVertex.ReadNodeVector().Vector + C_start.back()) * alpha +
                      (endVertex.ReadNodeVector().Vector - C_end) * (1.0f - alpha);
    }
    else
    {
        P_D1_plus_1 = startVertex.ReadNodeVector().Vector * alpha +
                      (endVertex.ReadNodeVector().Vector - C_end) * (1.0f - alpha);
    }
    controlPoints.push_back(P_D1_plus_1);
    std::cout << "P_D1_plus_1: " << P_D1_plus_1 << std::endl;

    // P_(D1+2) ~ P_n-1 (Equ. 20)
    for (int j = static_cast<int>(endBearings.size()) - 1; j >= 0; --j)
    {
        const auto& bearingEnd = endBearings[j];
        Vector3 C_j = bearingEnd.Vector * bearingEnd.Force.magnitude(); // Assuming Force magnitude as scalar
        Vector3 Pj = endVertex.ReadNodeVector().Vector - C_j; // Equ. 19에 따라 수정
        controlPoints.push_back(Pj);
        std::cout << "Pj: " << Pj << std::endl;
    }

    // Pn = EndVertex's NodeVector (Equ. 21)
    controlPoints.push_back(endVertex.ReadNodeVector().Vector);
    std::cout << "Pn: " << endVertex.ReadNodeVector().Vector << std::endl;

    return controlPoints;
}

// Create B-Spline Line
void LinearSegment::CreateBSpline()
{
    // Calculate control points using the member variable alpha
    std::vector<Vector3> controlPoints = CalculateControlPoints(alpha);

    // Calculate B-Spline (approximated using Bezier curve)
    _linearSegmentCache->clear();
    for (int i = 0; i <= numSegments; ++i)
    {
        float t = static_cast<float>(i) / numSegments;
        Vector3 point = BezierPoint(controlPoints, t);
        _linearSegmentCache->push_back(point);
    }
}

// Create Polygon Vertices Based on LOD
std::vector<Vector3> LinearSegment::CreatePolygonVertices(int lod) const
{
    std::vector<Vector3> polygonVertices;

    // Implement vertex creation logic based on LOD (Equ. 26~29)
    if (!_linearSegmentCache->empty())
    {
        int step = std::max(1, static_cast<int>(_linearSegmentCache->size()) / lod);
        for (size_t i = 0; i < _linearSegmentCache->size(); i += step)
        {
            polygonVertices.push_back((*_linearSegmentCache)[i]);
        }
        // Add the last point if not already included
        const Vector3& lastPoint = _linearSegmentCache->back();
        if (polygonVertices.empty() ||
            std::abs(polygonVertices.back().x - lastPoint.x) > 1e-5 ||
            std::abs(polygonVertices.back().y - lastPoint.y) > 1e-5 ||
            std::abs(polygonVertices.back().z - lastPoint.z) > 1e-5)
        {
            polygonVertices.push_back(lastPoint);
        }
    }

    return polygonVertices;
}

// Get Cached Segment Data
std::shared_ptr<std::vector<Vector3>> LinearSegment::GetLinearSegmentCache() const
{
    return _linearSegmentCache;
}

// Calculate Curvature (Equ. 22)
float LinearSegment::CalculateCurvature(float t) const
{
    // Retrieve control points (ensure the same alpha is used)
    std::vector<Vector3> controlPoints = CalculateControlPoints(alpha);

    // Calculate first and second derivatives
    Vector3 B_prime = BezierFirstDerivative(controlPoints, t);
    Vector3 B_double_prime = BezierSecondDerivative(controlPoints, t);

    // Calculate curvature: |B''(t) × B'(t)| / |B'(t)|^3 (Equ. 22)
    Vector3 crossProd = B_double_prime.cross(B_prime);
    float numerator = crossProd.magnitude();
    float denominator = powf(B_prime.magnitude(), 3);

    if (denominator == 0.0f)
        return 0.0f;

    return numerator / denominator;
}

// Setter for LOD
void LinearSegment::SetLOD(int newLOD)
{
    LOD = newLOD;
    // Automatically perform calculations upon update
    CreateBSpline();
}

// Setter for alpha
void LinearSegment::SetAlpha(float newAlpha)
{
    alpha = newAlpha;
    // Automatically perform calculations upon update
    CreateBSpline();
}

// Setter for numSegments
void LinearSegment::SetNumSegments(int newNumSegments)
{
    numSegments = newNumSegments;
    // Automatically perform calculations upon update
    CreateBSpline();
}

// Output Operator Overload Definition
std::ostream& operator<<(std::ostream& os, const LinearSegment& ls)
{
    os << "LinearSegment(StartVertex: " << ls.startVertex << ", EndVertex: " << ls.endVertex << ")";
    return os;
}
