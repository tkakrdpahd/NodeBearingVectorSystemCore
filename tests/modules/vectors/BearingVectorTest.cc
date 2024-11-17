// BearingVectorTest.cc
// Security: Top Secret
// Author: Minseok Doo
// Date: Nov 17, 2024
// 
// Purpose: Google Test unit tests for the BearingVector class and CoordinateConverter

#include <gtest/gtest.h>
#include "BearingVector.h"
#include "Vector3.h"
#include "NodeVector.h"
#include "CoordinateConverter.h"
#include <cmath>
#include <iostream>

// Vector3 비교 함수
bool areVectorsEqual(const Vector3& v1, const Vector3& v2, double epsilon = 1e-6) {
    return (std::abs(v1.x - v2.x) < epsilon) &&
           (std::abs(v1.y - v2.y) < epsilon) &&
           (std::abs(v1.z - v2.z) < epsilon);
}

// CoordinateConverter의 CartesianVector 비교 함수 (float 사용)
bool areVectorsEqual(const CartesianVector& v1, const CartesianVector& v2, float epsilon = 1e-5f) {
    return (std::abs(v1.x - v2.x) < epsilon) &&
           (std::abs(v1.y - v2.y) < epsilon) &&
           (std::abs(v1.z - v2.z) < epsilon);
}

// BearingVector 기본 생성자 테스트
TEST(BearingVectorTest, DefaultConstructor) {
    // 기본 NodeVector, Force, Vector 생성
    NodeVector defaultNode(0, Vector3());
    Vector3 defaultForce;
    Vector3 defaultVector;

    BearingVector bv(defaultNode, defaultForce, defaultVector);

    // 로그 출력
    std::cout << "BearingVectorTest.DefaultConstructor:" << std::endl;
    std::cout << "Node Vector = (" << bv.Node.Vector.x << ", " << bv.Node.Vector.y << ", " << bv.Node.Vector.z << ")" << std::endl;
    std::cout << "Force Vector = (" << bv.Force.x << ", " << bv.Force.y << ", " << bv.Force.z << ")" << std::endl;
    std::cout << "Vector = (" << bv.Vector.x << ", " << bv.Vector.y << ", " << bv.Vector.z << ")" << std::endl;

    // 기본값 검증
    EXPECT_EQ(bv.Node.Index, defaultNode.Index);
    EXPECT_TRUE(areVectorsEqual(bv.Force, defaultForce));
    EXPECT_TRUE(areVectorsEqual(bv.Vector, defaultVector));
}

// BearingVector 매개변수 생성자 테스트
TEST(BearingVectorTest, ParameterizedConstructor) {
    // 테스트 데이터 설정
    int testIndex = 1;
    Vector3 testVector(10.0, 20.0, 30.0);
    NodeVector testNode(testIndex, testVector);

    Vector3 testForce(5.0, -3.0, 2.5);
    Vector3 testVectorBv(100.0, 45.0, 60.0);

    // BearingVector 인스턴스 생성
    BearingVector bv(testNode, testForce, testVectorBv);

    // 로그 출력
    std::cout << "BearingVectorTest.ParameterizedConstructor:" << std::endl;
    std::cout << "Node Vector = (" << bv.Node.Vector.x << ", " << bv.Node.Vector.y << ", " << bv.Node.Vector.z << ")" << std::endl;
    std::cout << "Force Vector = (" << bv.Force.x << ", " << bv.Force.y << ", " << bv.Force.z << ")" << std::endl;
    std::cout << "Vector = (" << bv.Vector.x << ", " << bv.Vector.y << ", " << bv.Vector.z << ")" << std::endl;

    // 멤버 변수 검증
    EXPECT_EQ(bv.Node.Index, testIndex);
    EXPECT_TRUE(areVectorsEqual(bv.Node.Vector, testVector));
    EXPECT_TRUE(areVectorsEqual(bv.Force, testForce));
    EXPECT_TRUE(areVectorsEqual(bv.Vector, testVectorBv));
}

// BearingVector 멤버 변수 수정 테스트
TEST(BearingVectorTest, MemberVariableModification) {
    // 초기 데이터 설정
    NodeVector node(2, Vector3(15.0, 25.0, 35.0));
    Vector3 force(7.5, -4.5, 3.0);
    Vector3 vec(150.0, 60.0, 75.0);

    BearingVector bv(node, force, vec);

    // 멤버 변수 수정
    bv.Node.Index = 3;
    bv.Node.Vector = Vector3(20.0, 30.0, 40.0);
    bv.Force = Vector3(10.0, -5.0, 4.0);
    bv.Vector = Vector3(200.0, 75.0, 90.0);

    // 로그 출력
    std::cout << "BearingVectorTest.MemberVariableModification:" << std::endl;
    std::cout << "Modified Node Vector = (" << bv.Node.Vector.x << ", " << bv.Node.Vector.y << ", " << bv.Node.Vector.z << ")" << std::endl;
    std::cout << "Modified Force Vector = (" << bv.Force.x << ", " << bv.Force.y << ", " << bv.Force.z << ")" << std::endl;
    std::cout << "Modified Vector = (" << bv.Vector.x << ", " << bv.Vector.y << ", " << bv.Vector.z << ")" << std::endl;

    // 수정된 값 검증
    EXPECT_EQ(bv.Node.Index, 3);
    EXPECT_TRUE(areVectorsEqual(bv.Node.Vector, Vector3(20.0, 30.0, 40.0)));
    EXPECT_TRUE(areVectorsEqual(bv.Force, Vector3(10.0, -5.0, 4.0)));
    EXPECT_TRUE(areVectorsEqual(bv.Vector, Vector3(200.0, 75.0, 90.0)));
}

// BearingVector 복사 생성자 테스트
TEST(BearingVectorTest, CopyConstructor) {
    // 원본 데이터 설정
    NodeVector originalNode(4, Vector3(25.0, 35.0, 45.0));
    Vector3 originalForce(12.0, -6.0, 5.0);
    Vector3 originalVector(250.0, 90.0, 105.0);

    BearingVector originalBV(originalNode, originalForce, originalVector);

    // 복사 생성자 사용
    BearingVector copiedBV(originalBV);

    // 로그 출력
    std::cout << "BearingVectorTest.CopyConstructor:" << std::endl;
    std::cout << "Original Node Vector = (" << originalBV.Node.Vector.x << ", " << originalBV.Node.Vector.y << ", " << originalBV.Node.Vector.z << ")" << std::endl;
    std::cout << "Original Force Vector = (" << originalBV.Force.x << ", " << originalBV.Force.y << ", " << originalBV.Force.z << ")" << std::endl;
    std::cout << "Original Vector = (" << originalBV.Vector.x << ", " << originalBV.Vector.y << ", " << originalBV.Vector.z << ")" << std::endl;

    std::cout << "Copied Node Vector = (" << copiedBV.Node.Vector.x << ", " << copiedBV.Node.Vector.y << ", " << copiedBV.Node.Vector.z << ")" << std::endl;
    std::cout << "Copied Force Vector = (" << copiedBV.Force.x << ", " << copiedBV.Force.y << ", " << copiedBV.Force.z << ")" << std::endl;
    std::cout << "Copied Vector = (" << copiedBV.Vector.x << ", " << copiedBV.Vector.y << ", " << copiedBV.Vector.z << ")" << std::endl;

    // 복사된 값 검증
    EXPECT_EQ(copiedBV.Node.Index, originalBV.Node.Index);
    EXPECT_TRUE(areVectorsEqual(copiedBV.Node.Vector, originalBV.Node.Vector));
    EXPECT_TRUE(areVectorsEqual(copiedBV.Force, originalBV.Force));
    EXPECT_TRUE(areVectorsEqual(copiedBV.Vector, originalBV.Vector));
}

// BearingVector 대입 연산자 테스트
TEST(BearingVectorTest, AssignmentOperator) {
    // 원본 데이터 설정
    NodeVector originalNode(5, Vector3(30.0, 40.0, 50.0));
    Vector3 originalForce(15.0, -7.5, 6.0);
    Vector3 originalVector(300.0, 120.0, 135.0);

    BearingVector originalBV(originalNode, originalForce, originalVector);

    // 대상 BearingVector 생성 후 대입
    BearingVector assignedBV;
    assignedBV = originalBV;

    // 로그 출력
    std::cout << "BearingVectorTest.AssignmentOperator:" << std::endl;
    std::cout << "Original Node Vector = (" << originalBV.Node.Vector.x << ", " << originalBV.Node.Vector.y << ", " << originalBV.Node.Vector.z << ")" << std::endl;
    std::cout << "Original Force Vector = (" << originalBV.Force.x << ", " << originalBV.Force.y << ", " << originalBV.Force.z << ")" << std::endl;
    std::cout << "Original Vector = (" << originalBV.Vector.x << ", " << originalBV.Vector.y << ", " << originalBV.Vector.z << ")" << std::endl;

    std::cout << "Assigned Node Vector = (" << assignedBV.Node.Vector.x << ", " << assignedBV.Node.Vector.y << ", " << assignedBV.Node.Vector.z << ")" << std::endl;
    std::cout << "Assigned Force Vector = (" << assignedBV.Force.x << ", " << assignedBV.Force.y << ", " << assignedBV.Force.z << ")" << std::endl;
    std::cout << "Assigned Vector = (" << assignedBV.Vector.x << ", " << assignedBV.Vector.y << ", " << assignedBV.Vector.z << ")" << std::endl;

    // 대입된 값 검증
    EXPECT_EQ(assignedBV.Node.Index, originalBV.Node.Index);
    EXPECT_TRUE(areVectorsEqual(assignedBV.Node.Vector, originalBV.Node.Vector));
    EXPECT_TRUE(areVectorsEqual(assignedBV.Force, originalBV.Force));
    EXPECT_TRUE(areVectorsEqual(assignedBV.Vector, originalBV.Vector));
}

// CoordinateConverter: Spherical to Cartesian 변환 테스트
TEST(CoordinateConverterTest, SphericalToCartesian) {
    // 테스트 데이터 설정 (반지름 r, 각도 theta, phi)
    SphericalVector sv(10.0f, M_PI / 4, M_PI / 3); // r=10, theta=45도, phi=60도

    // 기대되는 직교 좌표 계산
    // x = 10 * sin(60°) * cos(45°) = 10 * (√3/2) * (√2/2) = 10 * √6 / 4 ≈ 6.12372
    // y = 10 * sin(60°) * sin(45°) = 10 * (√3/2) * (√2/2) = 10 * √6 / 4 ≈ 6.12372
    // z = 10 * cos(60°) = 10 * 0.5 = 5.0
    CartesianVector expected_cv(6.123724f, 6.123724f, 5.0f);

    // 변환 수행
    CartesianVector cv = CoordinateConverter::sphericalToCartesian(sv);

    // 로그 출력
    std::cout << "CoordinateConverterTest.SphericalToCartesian:" << std::endl;
    std::cout << "Original Spherical Vector = (r: " << sv.r << ", theta: " << sv.theta << ", phi: " << sv.phi << ")" << std::endl;
    std::cout << "Converted Cartesian Vector = (" << cv.x << ", " << cv.y << ", " << cv.z << ")" << std::endl;
    std::cout << "Expected Cartesian Vector = (" << expected_cv.x << ", " << expected_cv.y << ", " << expected_cv.z << ")" << std::endl;

    // 변환 결과 검증
    EXPECT_TRUE(areVectorsEqual(cv, expected_cv));
}

// CoordinateConverter: Cartesian to Spherical 변환 테스트
TEST(CoordinateConverterTest, CartesianToSpherical) {
    // 테스트 데이터 설정 (x, y, z)
    CartesianVector cv(6.123724f, 6.123724f, 5.0f);

    // 기대되는 구면 좌표 계산
    // r = sqrt(x^2 + y^2 + z^2) = sqrt(6.123724^2 + 6.123724^2 + 5^2) = sqrt(37.5 + 37.5 + 25) = sqrt(100) = 10
    // theta = atan2(y, x) = atan2(6.123724, 6.123724) = 45도 = π/4
    // phi = acos(z / r) = acos(5 / 10) = acos(0.5) = 60도 = π/3
    SphericalVector expected_sv(10.0f, M_PI / 4, M_PI / 3);

    // 변환 수행
    SphericalVector sv = CoordinateConverter::cartesianToSpherical(cv);

    // 로그 출력
    std::cout << "CoordinateConverterTest.CartesianToSpherical:" << std::endl;
    std::cout << "Original Cartesian Vector = (" << cv.x << ", " << cv.y << ", " << cv.z << ")" << std::endl;
    std::cout << "Converted Spherical Vector = (r: " << sv.r << ", theta: " << sv.theta << ", phi: " << sv.phi << ")" << std::endl;
    std::cout << "Expected Spherical Vector = (r: " << expected_sv.r << ", theta: " << expected_sv.theta << ", phi: " << expected_sv.phi << ")" << std::endl;

    // 변환 결과 검증 (오차 범위 고려)
    EXPECT_NEAR(sv.r, expected_sv.r, 1e-5f);
    EXPECT_NEAR(sv.theta, expected_sv.theta, 1e-5f);
    EXPECT_NEAR(sv.phi, expected_sv.phi, 1e-5f);
}

// CoordinateConverter: Spherical <-> Cartesian 상호 변환 테스트
TEST(CoordinateConverterTest, SphericalToCartesianToSpherical) {
    // 초기 구면 좌표 설정
    SphericalVector original_sv(15.0f, M_PI / 6, M_PI / 4); // r=15, theta=30도, phi=45도

    // 구면 -> 직교 변환
    CartesianVector cv = CoordinateConverter::sphericalToCartesian(original_sv);

    // 직교 -> 구면 변환
    SphericalVector converted_sv = CoordinateConverter::cartesianToSpherical(cv);

    // 로그 출력
    std::cout << "CoordinateConverterTest.SphericalToCartesianToSpherical:" << std::endl;
    std::cout << "Original Spherical Vector = (r: " << original_sv.r << ", theta: " << original_sv.theta << ", phi: " << original_sv.phi << ")" << std::endl;
    std::cout << "Converted Cartesian Vector = (" << cv.x << ", " << cv.y << ", " << cv.z << ")" << std::endl;
    std::cout << "Converted Spherical Vector = (r: " << converted_sv.r << ", theta: " << converted_sv.theta << ", phi: " << converted_sv.phi << ")" << std::endl;

    // 원본과 변환된 구면 좌표 비교 (오차 범위 고려)
    EXPECT_NEAR(converted_sv.r, original_sv.r, 1e-5f);
    EXPECT_NEAR(converted_sv.theta, original_sv.theta, 1e-5f);
    EXPECT_NEAR(converted_sv.phi, original_sv.phi, 1e-5f);
}
