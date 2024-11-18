// BearingVectorTest.cc
// Security: Top Secret
// Author: Minseok Doo
// Date: Nov 17, 2024
//
// Purpose: Unit tests for the BearingVector class

#include <gtest/gtest.h>
#include "BearingVector.h"
#include "Vector3.h"
#include "NodeVector.h"
#include <cmath>
#include <iostream>

// Vector3 비교 함수
bool areVectorsEqual(const Vector3& v1, const Vector3& v2, double epsilon = 1e-6) {
    return (std::abs(v1.x - v2.x) < epsilon) &&
           (std::abs(v1.y - v2.y) < epsilon) &&
           (std::abs(v1.z - v2.z) < epsilon);
}

// 로그 출력 헬퍼 함수
void logBearingVector(const BearingVector& bv) {
    std::cout << "Node Index: " << bv.Node.Index << std::endl;
    std::cout << "Force: (" << bv.Force.x << ", " << bv.Force.y << ", " << bv.Force.z << ")" << std::endl;
    std::cout << "Vector: (" << bv.Vector.x << ", " << bv.Vector.y << ", " << bv.Vector.z << ")" << std::endl;
}

// BearingVector 기본 생성자 테스트
TEST(BearingVectorTest, DefaultConstructor) {
    BearingVector bv;

    std::cout << "BearingVectorTest.DefaultConstructor:" << std::endl;
    logBearingVector(bv);

    EXPECT_EQ(bv.Node.Index, 0);
    EXPECT_TRUE(areVectorsEqual(bv.Force, Vector3()));
    EXPECT_TRUE(areVectorsEqual(bv.Vector, Vector3()));
}

// BearingVector 매개변수 생성자 테스트
TEST(BearingVectorTest, ParameterizedConstructor) {
    int testIndex = 1;
    Vector3 nodeVec(10.0f, 20.0f, 30.0f); // 예시 NodeVector의 Vector3 값
    NodeVector node(testIndex, nodeVec);
    Vector3 testForce(5.0f, -3.0f, 2.5f);
    Vector3 testVector(100.0f, 45.0f, 60.0f);

    BearingVector bv(node, testForce, testVector);

    std::cout << "BearingVectorTest.ParameterizedConstructor:" << std::endl;
    logBearingVector(bv);

    EXPECT_EQ(bv.Node.Index, testIndex);
    EXPECT_TRUE(areVectorsEqual(bv.Force, testForce));
    EXPECT_TRUE(areVectorsEqual(bv.Vector, testVector));
}

// BearingVector 멤버 변수 수정 테스트
TEST(BearingVectorTest, MemberVariableModification) {
    int initialIndex = 2;
    Vector3 initialNodeVec(15.0f, 25.0f, 35.0f); // 예시 NodeVector의 Vector3 값
    NodeVector node(initialIndex, initialNodeVec);
    Vector3 initialForce(7.5f, -4.5f, 3.0f);
    Vector3 initialVector(150.0f, 60.0f, 75.0f);

    BearingVector bv(node, initialForce, initialVector);

    bv.Node.Index = 3;
    bv.Force = Vector3(10.0f, -5.0f, 4.0f);
    bv.Vector = Vector3(200.0f, 75.0f, 90.0f);

    std::cout << "BearingVectorTest.MemberVariableModification:" << std::endl;
    logBearingVector(bv);

    EXPECT_EQ(bv.Node.Index, 3);
    EXPECT_TRUE(areVectorsEqual(bv.Force, Vector3(10.0f, -5.0f, 4.0f)));
    EXPECT_TRUE(areVectorsEqual(bv.Vector, Vector3(200.0f, 75.0f, 90.0f)));
}

// BearingVector 복사 생성자 테스트
TEST(BearingVectorTest, CopyConstructor) {
    int originalIndex = 4;
    Vector3 originalNodeVec(20.0f, 30.0f, 40.0f); // 예시 NodeVector의 Vector3 값
    NodeVector originalNode(originalIndex, originalNodeVec);
    Vector3 originalForce(12.0f, -6.0f, 5.0f);
    Vector3 originalVector(250.0f, 90.0f, 105.0f);

    BearingVector originalBV(originalNode, originalForce, originalVector);

    BearingVector copiedBV(originalBV);

    std::cout << "BearingVectorTest.CopyConstructor:" << std::endl;
    logBearingVector(copiedBV);

    EXPECT_EQ(copiedBV.Node.Index, originalBV.Node.Index);
    EXPECT_TRUE(areVectorsEqual(copiedBV.Force, originalBV.Force));
    EXPECT_TRUE(areVectorsEqual(copiedBV.Vector, originalBV.Vector));
}

// BearingVector 대입 연산자 테스트
TEST(BearingVectorTest, AssignmentOperator) {
    int originalIndex = 5;
    Vector3 originalNodeVec(25.0f, 35.0f, 45.0f); // 예시 NodeVector의 Vector3 값
    NodeVector originalNode(originalIndex, originalNodeVec);
    Vector3 originalForce(15.0f, -7.5f, 6.0f);
    Vector3 originalVector(300.0f, 120.0f, 135.0f);

    BearingVector originalBV(originalNode, originalForce, originalVector);

    BearingVector assignedBV;
    assignedBV = originalBV;

    std::cout << "BearingVectorTest.AssignmentOperator:" << std::endl;
    logBearingVector(assignedBV);

    EXPECT_EQ(assignedBV.Node.Index, originalBV.Node.Index);
    EXPECT_TRUE(areVectorsEqual(assignedBV.Force, originalBV.Force));
    EXPECT_TRUE(areVectorsEqual(assignedBV.Vector, originalBV.Vector));
}

// BearingVector 전체 테스트
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
