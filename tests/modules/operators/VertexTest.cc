// VertexTest.cc

#include <gtest/gtest.h>
#include "Vertex.h"
#include "NodeVector.h"     // NodeVector를 사용하기 위해 포함
#include "BearingVector.h"  // BearingVector를 사용하기 위해 포함
#include <memory>

// 테스트 케이스 1: 생성자 검증
TEST(VertexTest, ConstructorInitializesCorrectly) {
    Vertex vertex;
    EXPECT_NO_THROW(vertex.ReadNodeVector());
    // EXPECT_NO_THROW(vertex.GetBearingVector()); // 존재하지 않는 메소드 호출 제거
}

// 테스트 케이스 2: CreateAndUpdateNodeVector
TEST(VertexTest, CreateAndUpdateNodeVector) {
    Vertex vertex;

    // NodeVector 업데이트 및 값 확인
    NodeVector newNode(1, Vector3(1.0f, 2.0f, 3.0f));
    vertex.UpdateNodeVector(newNode);

    // ReadNodeVector을 통해 값을 직접 비교
    EXPECT_EQ(vertex.ReadNodeVector().Index, 1);
    EXPECT_EQ(vertex.ReadNodeVector().Vector, Vector3(1.0f, 2.0f, 3.0f));
}

// 테스트 케이스 3: AddAndReadBearingVectors
TEST(VertexTest, AddAndReadBearingVectors) {
    Vertex vertex;

    // BearingVector 추가
    NodeVector node0(0, Vector3(0.0f, 0.0f, 0.0f)); // BearingVector에 필요한 NodeVector
    BearingVector bearing1(node0, Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 2.0f));
    BearingVector bearing2(node0, Vector3(0.0f, 1.0f, 0.0f), Vector3(3.0f, 4.0f, 5.0f));

    vertex.PostBearingVector(bearing1);
    vertex.PostBearingVector(bearing2);

    // BearingVectorList 크기 확인
    EXPECT_EQ(vertex.ReadBearingVectorList().size(), 2);

    // BearingVector의 내용 확인
    EXPECT_EQ(vertex.ReadBearingVectorList()[0].Vector, Vector3(0.0f, 1.0f, 2.0f));
    EXPECT_EQ(vertex.ReadBearingVectorList()[1].Vector, Vector3(3.0f, 4.0f, 5.0f));
}

// 테스트 케이스 4: UpdateAndDeleteBearingVectors
TEST(VertexTest, UpdateAndDeleteBearingVectors) {
    Vertex vertex;

    // BearingVector 추가
    NodeVector node0(0, Vector3(0.0f, 0.0f, 0.0f));
    BearingVector bearing(node0, Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 2.0f));
    vertex.PostBearingVector(bearing);

    // BearingVector 업데이트
    BearingVector newBearing(node0, Vector3(0.0f, 0.0f, 1.0f), Vector3(7.0f, 8.0f, 9.0f));
    vertex.PutBearingVector(newBearing);

    // 업데이트된 BearingVector 확인
    EXPECT_EQ(vertex.ReadBearingVectorList().size(), 1);
    EXPECT_EQ(vertex.ReadBearingVectorList()[0].Vector, Vector3(7.0f, 8.0f, 9.0f));

    // BearingVector 삭제
    vertex.DeleteBearingVector();

    // BearingVectorList 크기 확인
    EXPECT_EQ(vertex.ReadBearingVectorList().size(), 0);
}

// 테스트 케이스 5: BearingVectorListLifecycle
TEST(VertexTest, BearingVectorListLifecycle) {
    Vertex vertex;

    // BearingVector 추가
    NodeVector node0(0, Vector3(0.0f, 0.0f, 0.0f));
    BearingVector bearing(node0, Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 2.0f));
    vertex.PostBearingVector(bearing);

    // BearingVector 삭제
    vertex.DeleteBearingVector();

    // BearingVectorList 크기 확인
    EXPECT_EQ(vertex.ReadBearingVectorList().size(), 0);
}

// 메인 함수: 모든 테스트 실행
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
