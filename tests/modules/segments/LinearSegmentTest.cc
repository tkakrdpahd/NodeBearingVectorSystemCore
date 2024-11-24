// LinearSegmentTest.cc

#include <gtest/gtest.h>
#include <sstream>

// 포함해야 할 헤더 파일들
#include "LinearSegment.h"
#include "Vector3.h"
#include "NodeVector.h"
#include "BearingVector.h"
#include "Vertex.h"

// 테스트 클래스 정의
class LinearSegmentTest : public ::testing::Test {
protected:
    // 테스트 시작 전에 실행되는 SetUp 함수
    void SetUp() override {
        // Start Vertex 초기화
        NodeVector startNode(0, Vector3(0.0f, 0.0f, 0.0f));
        startVertex.UpdateNodeVector(startNode);
        
        // BearingVector 생성: x축 방향으로 설정하여 직선 보장
        BearingVector startBearing1(startNode, Vector3(1.0f, 0.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));
        BearingVector startBearing2(startNode, Vector3(1.0f, 0.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));
        startVertex.PostBearingVector(startBearing1);
        startVertex.PostBearingVector(startBearing2);

        // End Vertex 초기화
        NodeVector endNode(1, Vector3(10.0f, 0.0f, 0.0f));
        endVertex.UpdateNodeVector(endNode);
        
        // BearingVector 생성: x축 방향으로 설정하여 직선 보장
        BearingVector endBearing1(endNode, Vector3(1.0f, 0.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));
        BearingVector endBearing2(endNode, Vector3(1.0f, 0.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));
        endVertex.PostBearingVector(endBearing1);
        endVertex.PostBearingVector(endBearing2);

        // LinearSegment 객체 생성
        linearSegment = new LinearSegment(startVertex, endVertex, 0.5f, 10);
    }

    // 테스트 종료 후 실행되는 TearDown 함수
    void TearDown() override {
        delete linearSegment;
    }

    // 테스트에 사용할 객체들
    Vertex startVertex;
    Vertex endVertex;
    LinearSegment* linearSegment;
};

// 테스트 케이스 1: 생성자 검증
TEST_F(LinearSegmentTest, ConstructorTest) {
    EXPECT_EQ(linearSegment->ReadLOD(), 1);
    
    // Vertex 기반 조회
    EXPECT_EQ(linearSegment->GetStartVertex().ReadNodeVector().Vector, Vector3(0.0f, 0.0f, 0.0f));
    EXPECT_EQ(linearSegment->GetEndVertex().ReadNodeVector().Vector, Vector3(10.0f, 0.0f, 0.0f));

    EXPECT_EQ(linearSegment->GetStartVertex().ReadBearingVectorList().size(), 2);
    EXPECT_EQ(linearSegment->GetEndVertex().ReadBearingVectorList().size(), 2);
}

// 테스트 케이스 2: BSpline 캐시 크기 검증
TEST_F(LinearSegmentTest, BSplineCacheSizeTest) {
    auto cache = linearSegment->GetLinearSegmentCache();
    EXPECT_EQ(cache->size(), 11); // numSegments = 10, 따라서 11개의 포인트
}

// 테스트 케이스 3: SetAlpha 함수 검증
TEST_F(LinearSegmentTest, SetAlphaTest) {
    linearSegment->SetAlpha(0.5f);
    // alpha를 변경한 후 BSpline이 재계산되었는지 확인
    auto cache = linearSegment->GetLinearSegmentCache();
    EXPECT_EQ(cache->size(), 11); // numSegments는 동일하게 유지
    // 추가적인 검증을 원한다면, 특정 제어점의 값을 확인할 수 있습니다.
}

// 테스트 케이스 4: SetLOD 함수 검증
TEST_F(LinearSegmentTest, SetLODTest) {
    linearSegment->SetLOD(5);
    EXPECT_EQ(linearSegment->ReadLOD(), 5);
    // LOD 변경에 따른 추가적인 동작을 검증할 수 있습니다.
}

// 테스트 케이스 5: SetNumSegments 함수 검증
TEST_F(LinearSegmentTest, SetNumSegmentsTest) {
    linearSegment->SetNumSegments(20);
    EXPECT_EQ(linearSegment->GetLinearSegmentCache()->size(), 21); // numSegments = 20, 따라서 21개의 포인트
}

// 테스트 케이스 6: Curvature 계산 검증
TEST_F(LinearSegmentTest, CalculateCurvatureTest) {
    // 곡률 계산은 public 함수로 가정하고 직접 호출 가능
    // 현재 직선 경로이므로, 모든 t에서 곡률은 0이어야 합니다.
    for (int i = 0; i <= 10; ++i) {
        float t = static_cast<float>(i) / 10.0f;
        float curvature = linearSegment->CalculateCurvature(t);
        EXPECT_NEAR(curvature, 0.0f, 1e-3f);
    }
}

// 테스트 케이스 7: operator<< 오버로드 검증
TEST_F(LinearSegmentTest, OperatorOutputTest) {
    std::ostringstream oss;
    oss << *linearSegment;
    std::string output = oss.str();

    // 예상 출력 문자열이 정확히 일치하는지 확인
    std::string expectedOutput = "LinearSegment(StartVertex: Vertex(Index: 0, NodeVector: NodeVector(Index: 0, Vector: (0, 0, 0))), EndVertex: Vertex(Index: 1, NodeVector: NodeVector(Index: 1, Vector: (10, 0, 0))))";
    EXPECT_EQ(output, expectedOutput);
}

// 테스트 케이스 8: BSpline 포인트 정확도 검증
TEST_F(LinearSegmentTest, BSplinePointAccuracyTest) {
    auto cache = linearSegment->GetLinearSegmentCache();
    // t=0에서의 포인트는 시작 노드와 동일해야 합니다.
    EXPECT_EQ((*cache)[0], Vector3(0.0f, 0.0f, 0.0f));
    // t=1에서의 포인트는 종료 노드와 동일해야 합니다.
    EXPECT_EQ((*cache)[10], Vector3(10.0f, 0.0f, 0.0f));

    // 중간 포인트의 예상 값을 검증할 수 있습니다.
    // 예를 들어, t=0.5에서 포인트가 (5,0,0)과 근사한지 확인
    Vector3 expectedMidPoint(5.0f, 0.0f, 0.0f); // 수정된 기대값
    EXPECT_NEAR((*cache)[5].x, expectedMidPoint.x, 1e-3f);
    EXPECT_NEAR((*cache)[5].y, expectedMidPoint.y, 1e-3f);
    EXPECT_NEAR((*cache)[5].z, expectedMidPoint.z, 1e-3f);
}

// 테스트 케이스 9: Control Points 계산 검증
TEST_F(LinearSegmentTest, CalculateControlPointsTest) {
    // Control Points을 계산하고 예상 값과 비교
    // CalculateControlPoints는 private으로 유지되었으므로, FRIEND_TEST를 통해 접근할 수 있습니다.
    std::vector<Vector3> controlPoints = linearSegment->CalculateControlPoints(0.5f);

    // 예상 제어점 개수는 1 (P0) + D1 (2) + 1 (P_D1+1) + D2 (2) + 1 (Pn) = 7개
    EXPECT_EQ(controlPoints.size(), 7);

    // 각 제어점의 값을 검증
    EXPECT_EQ(controlPoints[0], Vector3(0.0f, 0.0f, 0.0f)); // P0
    EXPECT_EQ(controlPoints[1], Vector3(1.0f, 0.0f, 0.0f)); // P1
    EXPECT_EQ(controlPoints[2], Vector3(1.0f, 0.0f, 0.0f)); // P2
    // P3 = 0.5 * (N1 + C1) + 0.5 * (N2 - C2) = 0.5*(0+1,0+0,0+0) + 0.5*(10-1,0-0,0-0) = (0.5,0,0) + (4.5,0,0) = (5,0,0)
    Vector3 expectedP3(5.0f, 0.0f, 0.0f); // 수정된 기대값
    EXPECT_NEAR(controlPoints[3].x, expectedP3.x, 1e-3f);
    EXPECT_NEAR(controlPoints[3].y, expectedP3.y, 1e-3f);
    EXPECT_NEAR(controlPoints[3].z, expectedP3.z, 1e-3f);
    
    // P4 = N2 - C_j (j=1) = (10,0,0) - (1,0,0) = (9,0,0)
    EXPECT_EQ(controlPoints[4], Vector3(9.0f, 0.0f, 0.0f));
    
    // P5 = N2 - C_j (j=2) = (10,0,0) - (1,0,0) = (9,0,0) // 동일한 BearingVector
    EXPECT_EQ(controlPoints[5], Vector3(9.0f, 0.0f, 0.0f));
    
    // Pn = N2
    EXPECT_EQ(controlPoints[6], Vector3(10.0f, 0.0f, 0.0f));
}
