// LinearSegment.cpp
#include "LinearSegment.h"

// 생성자
LinearSegment::LinearSegment(const NodeVector& start, const std::vector<BearingVector>& bearingStart,
                           const NodeVector& end, const std::vector<BearingVector>& bearingEnd)
    : NodeStart(start), BearingVectorStart(bearingStart),
      NodeEnd(end), BearingVectorEnd(bearingEnd),
      _linearSegmentCache(std::make_shared<std::vector<Vector3>>())
{
    // 초기화 코드 (필요 시)
}

// 소멸자
LinearSegment::~LinearSegment()
{
    // 정리 코드 (필요 시)
}

// 이항 계수 계산
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

// 베지어 곡선의 점 계산
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

// 베지어 곡선의 1차 도함수 계산
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

// 베지어 곡선의 2차 도함수 계산
Vector3 LinearSegment::BezierSecondDerivative(const std::vector<Vector3>& controlPoints, float t) const
{
    int n = static_cast<int>(controlPoints.size()) - 1;
    if (n < 2)
        return Vector3(0.0f, 0.0f, 0.0f); // 2차 도함수는 정의되지 않음

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

std::vector<Vector3> LinearSegment::CalculateControlPoints(float alpha) const
{
    std::vector<Vector3> controlPoints;

    // P0 = N1.Vector (Equ. 17)
    controlPoints.push_back(NodeStart.Vector);
    std::cout << "P0: " << controlPoints.back() << std::endl;

    // P1 ~ P_D1 (Equ. 18)
    std::vector<Vector3> C_start;
    for (const auto& bearing : BearingVectorStart)
    {
        Vector3 C_i = bearing.Vector * bearing.Force; // Hadamard product (B_i ⊗ F_i)
        C_start.push_back(C_i);
        Vector3 Pi = NodeStart.Vector + C_i;
        controlPoints.push_back(Pi);
        std::cout << "Pi: " << Pi << std::endl;
    }

    // P_(D1+1) = alpha * (N1 + C_(1,D1)) + (1 - alpha) * (N2 + C_(2,D2)) (Equ. 19)
    Vector3 C_end;
    if (!BearingVectorEnd.empty())
    {
        const auto& lastBearingEnd = BearingVectorEnd.back();
        C_end = lastBearingEnd.Vector * lastBearingEnd.Force;
    }
    else
    {
        C_end = Vector3(0.0f, 0.0f, 0.0f);
    }

    Vector3 P_D1_plus_1;
    if (!C_start.empty())
    {
        P_D1_plus_1 = (NodeStart.Vector + C_start.back()) * alpha + (NodeEnd.Vector + C_end) * (1.0f - alpha);
    }
    else
    {
        P_D1_plus_1 = NodeStart.Vector * alpha + (NodeEnd.Vector + C_end) * (1.0f - alpha);
    }
    controlPoints.push_back(P_D1_plus_1);
    std::cout << "P_D1_plus_1: " << P_D1_plus_1 << std::endl;

    // P_(D1+2) ~ P_n-1 (Equ. 20)
    for (int j = static_cast<int>(BearingVectorEnd.size()) - 1; j >= 0; --j)
    {
        const auto& bearingEnd = BearingVectorEnd[j];
        Vector3 C_j = bearingEnd.Vector * bearingEnd.Force; // Hadamard product (B_j ⊗ F_j)
        Vector3 Pj = NodeEnd.Vector + C_j; // 수정된 부분: '-'를 '+'로 변경
        controlPoints.push_back(Pj);
        std::cout << "Pj: " << Pj << std::endl;
    }

    // Pn = N2.Vector (Equ. 21)
    controlPoints.push_back(NodeEnd.Vector);
    std::cout << "Pn: " << NodeEnd.Vector << std::endl;

    return controlPoints;
}

// B-Spline 라인 생성
void LinearSegment::CreateBSpline(float alpha, int numSegments)
{
    // 컨트롤 포인트 계산
    std::vector<Vector3> controlPoints = CalculateControlPoints(alpha);

    // B-Spline 계산 (베지어 곡선으로 근사)
    _linearSegmentCache->clear();
    for (int i = 0; i <= numSegments; ++i)
    {
        float t = static_cast<float>(i) / numSegments;
        Vector3 point = BezierPoint(controlPoints, t);
        _linearSegmentCache->push_back(point);
    }
}

// LOD 기반 폴리곤 정점 생성
std::vector<Vector3> LinearSegment::CreatePolygonVertices(int lod) const
{
    std::vector<Vector3> polygonVertices;

    // LOD에 따른 정점 생성 로직 구현 (Equ. 26~29)
    if (!_linearSegmentCache->empty())
    {
        int step = std::max(1, static_cast<int>(_linearSegmentCache->size()) / lod);
        for (size_t i = 0; i < _linearSegmentCache->size(); i += step)
        {
            polygonVertices.push_back((*_linearSegmentCache)[i]);
        }
        // 마지막 점이 이미 포함되지 않았을 경우에만 추가
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

// 캐시된 선분 데이터 가져오기
std::shared_ptr<std::vector<Vector3>> LinearSegment::GetLinearSegmentCache() const
{
    return _linearSegmentCache;
}

// 곡률 계산 (Equ. 22)
float LinearSegment::CalculateCurvature(float t) const
{
    // 컨트롤 포인트 가져오기 (동일한 alpha 사용 필요)
    std::vector<Vector3> controlPoints = CalculateControlPoints(0.5f); // alpha = 0.5f 임의 설정

    // 1차 및 2차 도함수 계산
    Vector3 B_prime = BezierFirstDerivative(controlPoints, t);
    Vector3 B_double_prime = BezierSecondDerivative(controlPoints, t);

    // 곡률 계산: |B''(t) × B'(t)| / |B'(t)|^3 (Equ. 22)
    Vector3 crossProd = B_double_prime.cross(B_prime);
    float numerator = crossProd.magnitude();
    float denominator = powf(B_prime.magnitude(), 3);

    if (denominator == 0.0f)
        return 0.0f;

    return numerator / denominator;
}

// 출력 연산자 오버로드 정의
std::ostream& operator<<(std::ostream& os, const LinearSegment& ls)
{
    os << "LinearSegment(StartNode: " << ls.getStartNode() << ", EndNode: " << ls.getEndNode() << ")";
    return os;
}
