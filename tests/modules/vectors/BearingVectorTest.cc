// BearingVectorTest.cc
// Security: Top Secret
// Author: Minseok Doo
// Date: Nov 17, 2024
//
// Purpose: Unit tests for the BearingVector class

#include <gtest/gtest.h>
#include "BearingVector.h"
#include "Vector3.h"
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
    std::cout << "Node Index: " << bv.NodeIndex << std::endl;
    std::cout << "Force: (" << bv.Force.x << ", " << bv.Force.y << ", " << bv.Force.z << ")" << std::endl;
    std::cout << "Vector: (" << bv.Vector.x << ", " << bv.Vector.y << ", " << bv.Vector.z << ")" << std::endl;
}

// BearingVector 기본 생성자 테스트
TEST(BearingVectorTest, DefaultConstructor) {
    BearingVector bv;

    std::cout << "BearingVectorTest.DefaultConstructor:" << std::endl;
    logBearingVector(bv);

    EXPECT_EQ(bv.NodeIndex, 0);
    EXPECT_TRUE(areVectorsEqual(bv.Force, Vector3()));
    EXPECT_TRUE(areVectorsEqual(bv.Vector, Vector3()));
}

// BearingVector 매개변수 생성자 테스트
TEST(BearingVectorTest, ParameterizedConstructor) {
    int testIndex = 1;
    Vector3 testForce(5.0, -3.0, 2.5);
    Vector3 testVector(100.0, 45.0, 60.0);

    BearingVector bv(testIndex, testForce, testVector);

    std::cout << "BearingVectorTest.ParameterizedConstructor:" << std::endl;
    logBearingVector(bv);

    EXPECT_EQ(bv.NodeIndex, testIndex);
    EXPECT_TRUE(areVectorsEqual(bv.Force, testForce));
    EXPECT_TRUE(areVectorsEqual(bv.Vector, testVector));
}

// BearingVector 멤버 변수 수정 테스트
TEST(BearingVectorTest, MemberVariableModification) {
    int initialIndex = 2;
    Vector3 initialForce(7.5, -4.5, 3.0);
    Vector3 initialVector(150.0, 60.0, 75.0);

    BearingVector bv(initialIndex, initialForce, initialVector);

    bv.NodeIndex = 3;
    bv.Force = Vector3(10.0, -5.0, 4.0);
    bv.Vector = Vector3(200.0, 75.0, 90.0);

    std::cout << "BearingVectorTest.MemberVariableModification:" << std::endl;
    logBearingVector(bv);

    EXPECT_EQ(bv.NodeIndex, 3);
    EXPECT_TRUE(areVectorsEqual(bv.Force, Vector3(10.0, -5.0, 4.0)));
    EXPECT_TRUE(areVectorsEqual(bv.Vector, Vector3(200.0, 75.0, 90.0)));
}

// BearingVector 복사 생성자 테스트
TEST(BearingVectorTest, CopyConstructor) {
    int originalIndex = 4;
    Vector3 originalForce(12.0, -6.0, 5.0);
    Vector3 originalVector(250.0, 90.0, 105.0);

    BearingVector originalBV(originalIndex, originalForce, originalVector);

    BearingVector copiedBV(originalBV);

    std::cout << "BearingVectorTest.CopyConstructor:" << std::endl;
    logBearingVector(copiedBV);

    EXPECT_EQ(copiedBV.NodeIndex, originalBV.NodeIndex);
    EXPECT_TRUE(areVectorsEqual(copiedBV.Force, originalBV.Force));
    EXPECT_TRUE(areVectorsEqual(copiedBV.Vector, originalBV.Vector));
}

// BearingVector 대입 연산자 테스트
TEST(BearingVectorTest, AssignmentOperator) {
    int originalIndex = 5;
    Vector3 originalForce(15.0, -7.5, 6.0);
    Vector3 originalVector(300.0, 120.0, 135.0);

    BearingVector originalBV(originalIndex, originalForce, originalVector);

    BearingVector assignedBV;
    assignedBV = originalBV;

    std::cout << "BearingVectorTest.AssignmentOperator:" << std::endl;
    logBearingVector(assignedBV);

    EXPECT_EQ(assignedBV.NodeIndex, originalBV.NodeIndex);
    EXPECT_TRUE(areVectorsEqual(assignedBV.Force, originalBV.Force));
    EXPECT_TRUE(areVectorsEqual(assignedBV.Vector, originalBV.Vector));
}

// BearingVector 전체 테스트
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
