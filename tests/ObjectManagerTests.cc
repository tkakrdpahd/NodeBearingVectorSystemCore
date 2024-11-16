// test/ObjectManagerTests.cpp

#include <gtest/gtest.h>
#include "ObjectManager.h"
#include "Vector3.h"
#include "NodeVector.h"
#include "BearingVector.h"

// Fixture 클래스 정의 (필요에 따라 사용)
class ObjectManagerTest : public ::testing::Test {
protected:
    ObjectManager manager;

    void SetUp() override {
        // 초기화 작업이 필요하면 여기에 추가
    }

    void TearDown() override {
        // 정리 작업이 필요하면 여기에 추가
    }
};

// 테스트 케이스: NodeVector 생성
TEST_F(ObjectManagerTest, CreateNodeVector_Success) {
    Vector3 vec(1.0f, 2.0f, 3.0f);
    int index = 100;
    auto node = manager.CreateNodeVector(index, vec);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->index, index);
    EXPECT_FLOAT_EQ(node->vector.x, 1.0f);
    EXPECT_FLOAT_EQ(node->vector.y, 2.0f);
    EXPECT_FLOAT_EQ(node->vector.z, 3.0f);
}

// 테스트 케이스: NodeVector 중복 생성 실패
TEST_F(ObjectManagerTest, CreateNodeVector_DuplicateIndex) {
    Vector3 vec1(1.0f, 2.0f, 3.0f);
    Vector3 vec2(4.0f, 5.0f, 6.0f);
    int index = 101;
    auto node1 = manager.CreateNodeVector(index, vec1);
    ASSERT_NE(node1, nullptr);
    auto node2 = manager.CreateNodeVector(index, vec2);
    EXPECT_EQ(node2, nullptr);
}

// 테스트 케이스: NodeVector 읽기 성공
TEST_F(ObjectManagerTest, ReadNodeVector_Success) {
    Vector3 vec(7.0f, 8.0f, 9.0f);
    int index = 102;
    manager.CreateNodeVector(index, vec);
    auto node = manager.ReadNodeVector(index);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->index, index);
    EXPECT_FLOAT_EQ(node->vector.x, 7.0f);
    EXPECT_FLOAT_EQ(node->vector.y, 8.0f);
    EXPECT_FLOAT_EQ(node->vector.z, 9.0f);
}

// 테스트 케이스: NodeVector 읽기 실패 (존재하지 않는 인덱스)
TEST_F(ObjectManagerTest, ReadNodeVector_NotFound) {
    int index = 103;
    auto node = manager.ReadNodeVector(index);
    EXPECT_EQ(node, nullptr);
}

// 테스트 케이스: NodeVector 업데이트 성공
TEST_F(ObjectManagerTest, UpdateNodeVector_Success) {
    Vector3 vec1(10.0f, 11.0f, 12.0f);
    Vector3 vec2(13.0f, 14.0f, 15.0f);
    int index = 104;
    manager.CreateNodeVector(index, vec1);
    auto updatedNode = manager.UpdateNodeVector(index, vec2);
    ASSERT_NE(updatedNode, nullptr);
    EXPECT_FLOAT_EQ(updatedNode->vector.x, 13.0f);
    EXPECT_FLOAT_EQ(updatedNode->vector.y, 14.0f);
    EXPECT_FLOAT_EQ(updatedNode->vector.z, 15.0f);
}

// 테스트 케이스: NodeVector 업데이트 실패 (존재하지 않는 인덱스)
TEST_F(ObjectManagerTest, UpdateNodeVector_NotFound) {
    Vector3 vec(16.0f, 17.0f, 18.0f);
    int index = 105;
    auto updatedNode = manager.UpdateNodeVector(index, vec);
    EXPECT_EQ(updatedNode, nullptr);
}

// 테스트 케이스: NodeVector 삭제 성공
TEST_F(ObjectManagerTest, DeleteNodeVector_Success) {
    Vector3 vec(19.0f, 20.0f, 21.0f);
    int index = 106;
    manager.CreateNodeVector(index, vec);
    auto deletedNode = manager.DeleteNodeVector(index);
    ASSERT_NE(deletedNode, nullptr);
    EXPECT_EQ(deletedNode->index, index);
    EXPECT_EQ(manager.ReadNodeVector(index), nullptr);
}

// 테스트 케이스: NodeVector 삭제 실패 (존재하지 않는 인덱스)
TEST_F(ObjectManagerTest, DeleteNodeVector_NotFound) {
    int index = 107;
    auto deletedNode = manager.DeleteNodeVector(index);
    EXPECT_EQ(deletedNode, nullptr);
}

// 테스트 케이스: BearingVector 생성 성공
TEST_F(ObjectManagerTest, CreateBearingVector_Success) {
    // 먼저 NodeVector 생성
    Vector3 nodeVec(22.0f, 23.0f, 24.0f);
    int nodeIndex = 108;
    manager.CreateNodeVector(nodeIndex, nodeVec);

    Vector3 force(25.0f, 26.0f, 27.0f);
    Vector3 bearingVec(1.0f, 0.0f, 0.0f); // x=1 used as identifier
    auto bearing = manager.CreateBearingVector(nodeIndex, force, bearingVec);
    ASSERT_NE(bearing, nullptr);
    EXPECT_EQ(bearing->index, 1);
    EXPECT_FLOAT_EQ(bearing->force.x, 25.0f);
    EXPECT_FLOAT_EQ(bearing->force.y, 26.0f);
    EXPECT_FLOAT_EQ(bearing->force.z, 27.0f);
    EXPECT_FLOAT_EQ(bearing->vector.x, 1.0f);
    EXPECT_FLOAT_EQ(bearing->vector.y, 0.0f);
    EXPECT_FLOAT_EQ(bearing->vector.z, 0.0f);
}

// 테스트 케이스: BearingVector 생성 실패 (중복)
TEST_F(ObjectManagerTest, CreateBearingVector_Duplicate) {
    // 먼저 NodeVector 생성
    Vector3 nodeVec(28.0f, 29.0f, 30.0f);
    int nodeIndex = 109;
    manager.CreateNodeVector(nodeIndex, nodeVec);

    Vector3 force(31.0f, 32.0f, 33.0f);
    Vector3 bearingVec(2.0f, 0.0f, 0.0f); // x=2 used as identifier
    auto bearing1 = manager.CreateBearingVector(nodeIndex, force, bearingVec);
    ASSERT_NE(bearing1, nullptr);
    auto bearing2 = manager.CreateBearingVector(nodeIndex, force, bearingVec);
    EXPECT_EQ(bearing2, nullptr);
}

// 테스트 케이스: BearingVector 생성 실패 (존재하지 않는 NodeVector)
TEST_F(ObjectManagerTest, CreateBearingVector_NodeNotFound) {
    int nodeIndex = 110; // 존재하지 않는 NodeVector 인덱스
    Vector3 force(34.0f, 35.0f, 36.0f);
    Vector3 bearingVec(3.0f, 0.0f, 0.0f);
    auto bearing = manager.CreateBearingVector(nodeIndex, force, bearingVec);
    EXPECT_EQ(bearing, nullptr);
}

// 테스트 케이스: BearingVector 읽기 성공
TEST_F(ObjectManagerTest, ReadBearingVector_Success) {
    // NodeVector 생성
    Vector3 nodeVec(37.0f, 38.0f, 39.0f);
    int nodeIndex = 111;
    manager.CreateNodeVector(nodeIndex, nodeVec);

    Vector3 force(40.0f, 41.0f, 42.0f);
    Vector3 bearingVec(4.0f, 0.0f, 0.0f);
    manager.CreateBearingVector(nodeIndex, force, bearingVec);

    auto bearing = manager.ReadBearingVector(nodeIndex, bearingVec);
    ASSERT_NE(bearing, nullptr);
    EXPECT_EQ(bearing->index, 4);
    EXPECT_FLOAT_EQ(bearing->force.x, 40.0f);
    EXPECT_FLOAT_EQ(bearing->force.y, 41.0f);
    EXPECT_FLOAT_EQ(bearing->force.z, 42.0f);
    EXPECT_FLOAT_EQ(bearing->vector.x, 4.0f);
    EXPECT_FLOAT_EQ(bearing->vector.y, 0.0f);
    EXPECT_FLOAT_EQ(bearing->vector.z, 0.0f);
}

// 테스트 케이스: BearingVector 읽기 실패 (존재하지 않는 BearingVector)
TEST_F(ObjectManagerTest, ReadBearingVector_NotFound) {
    int nodeIndex = 112;
    Vector3 bearingVec(5.0f, 0.0f, 0.0f);
    auto bearing = manager.ReadBearingVector(nodeIndex, bearingVec);
    EXPECT_EQ(bearing, nullptr);
}

// 테스트 케이스: BearingVector 업데이트 성공
TEST_F(ObjectManagerTest, UpdateBearingVector_Success) {
    // NodeVector 생성
    Vector3 nodeVec(43.0f, 44.0f, 45.0f);
    int nodeIndex = 113;
    manager.CreateNodeVector(nodeIndex, nodeVec);

    Vector3 force1(46.0f, 47.0f, 48.0f);
    Vector3 bearingVec(6.0f, 0.0f, 0.0f);
    manager.CreateBearingVector(nodeIndex, force1, bearingVec);

    Vector3 force2(49.0f, 50.0f, 51.0f);
    Vector3 bearingVecUpdated(6.0f, 0.0f, 0.0f);
    auto updatedBearing = manager.UpdateBearingVector(nodeIndex, force2, bearingVecUpdated);
    ASSERT_NE(updatedBearing, nullptr);
    EXPECT_FLOAT_EQ(updatedBearing->force.x, 49.0f);
    EXPECT_FLOAT_EQ(updatedBearing->force.y, 50.0f);
    EXPECT_FLOAT_EQ(updatedBearing->force.z, 51.0f);
    EXPECT_FLOAT_EQ(updatedBearing->vector.x, 6.0f);
}

// 테스트 케이스: BearingVector 업데이트 실패 (존재하지 않는 BearingVector)
TEST_F(ObjectManagerTest, UpdateBearingVector_NotFound) {
    int nodeIndex = 114;
    Vector3 force(52.0f, 53.0f, 54.0f);
    Vector3 bearingVec(7.0f, 0.0f, 0.0f);
    auto updatedBearing = manager.UpdateBearingVector(nodeIndex, force, bearingVec);
    EXPECT_EQ(updatedBearing, nullptr);
}

// 테스트 케이스: BearingVector 삭제 성공
TEST_F(ObjectManagerTest, DeleteBearingVector_Success) {
    // NodeVector 생성
    Vector3 nodeVec(55.0f, 56.0f, 57.0f);
    int nodeIndex = 115;
    manager.CreateNodeVector(nodeIndex, nodeVec);

    Vector3 force(58.0f, 59.0f, 60.0f);
    Vector3 bearingVec(8.0f, 0.0f, 0.0f);
    manager.CreateBearingVector(nodeIndex, force, bearingVec);

    auto deletedBearing = manager.DeleteBearingVector(nodeIndex, bearingVec);
    ASSERT_NE(deletedBearing, nullptr);
    EXPECT_EQ(deletedBearing->vector.x, 8.0f);
    EXPECT_EQ(manager.ReadBearingVector(nodeIndex, bearingVec), nullptr);
}

// 테스트 케이스: BearingVector 삭제 실패 (존재하지 않는 BearingVector)
TEST_F(ObjectManagerTest, DeleteBearingVector_NotFound) {
    int nodeIndex = 116;
    Vector3 bearingVec(9.0f, 0.0f, 0.0f);
    auto deletedBearing = manager.DeleteBearingVector(nodeIndex, bearingVec);
    EXPECT_EQ(deletedBearing, nullptr);
}
