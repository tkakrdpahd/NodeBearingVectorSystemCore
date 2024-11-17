// tests/modules/vectors/NodeVectorTest.cc

#include <gtest/gtest.h>
#include <cmath> // for std::abs
#include <iostream> // for std::cout

#include "Vector3.h"
#include "CoordinateConverter.h"
#include "NodeVector.h"

// Define an epsilon for floating point comparison
const float EPSILON = 1e-5f;

// Helper function to print Vector3
void printVector3(const Vector3& vec, const std::string& name) {
    std::cout << name << " = (" << vec.x << ", " << vec.y << ", " << vec.z << ")\n";
}

// Helper function to print CartesianVector
void printCartesianVector(const CartesianVector& vec, const std::string& name) {
    std::cout << name << " = (" << vec.x << ", " << vec.y << ", " << vec.z << ")\n";
}

// Helper function to print SphericalVector
void printSphericalVector(const SphericalVector& vec, const std::string& name) {
    std::cout << name << " = (r: " << vec.r << ", theta: " << vec.theta << ", phi: " << vec.phi << ")\n";
}

TEST(CoordinateConverterTest, CartesianToSphericalAndBack) {
    // 초기 Cartesian 벡터 설정
    Vector3 originalVector(1.0f, 1.0f, 1.0f);
    printVector3(originalVector, "Original Vector");

    // NodeVector 객체 생성 (생성자 추가가 필요하거나 기본 생성 후 멤버 설정)
    NodeVector node(1, originalVector); // 생성자가 추가되었을 경우
    printVector3(node.Vector, "Node Vector");

    // CoordinateConverter 객체 생성
    CoordinateConverter coordinateConverter;

    // Vector3를 CartesianVector로 변환
    CartesianVector cartesianVec(node.Vector.x, node.Vector.y, node.Vector.z);
    printCartesianVector(cartesianVec, "Cartesian Vector");

    // Cartesian에서 Spherical으로 변환
    SphericalVector spherical = coordinateConverter.cartesianToSpherical(cartesianVec);
    printSphericalVector(spherical, "Spherical Vector");

    // Spherical에서 다시 Cartesian으로 변환
    CartesianVector convertedCartesian = coordinateConverter.sphericalToCartesian(spherical);
    printCartesianVector(convertedCartesian, "Converted Cartesian Vector");

    // 변환된 CartesianVector를 Vector3으로 변환
    Vector3 convertedVector(convertedCartesian.x, convertedCartesian.y, convertedCartesian.z);
    printVector3(convertedVector, "Converted Vector");

    // 변환된 벡터가 원래 벡터와 거의 같은지 확인
    EXPECT_NEAR(convertedVector.x, originalVector.x, EPSILON) << "X 좌표가 일치하지 않습니다.";
    EXPECT_NEAR(convertedVector.y, originalVector.y, EPSILON) << "Y 좌표가 일치하지 않습니다.";
    EXPECT_NEAR(convertedVector.z, originalVector.z, EPSILON) << "Z 좌표가 일치하지 않습니다.";
}

TEST(CoordinateConverterTest, OriginConversion) {
    Vector3 originalVector(0.0f, 0.0f, 0.0f);
    printVector3(originalVector, "Original Vector (Origin)");

    NodeVector node(0, originalVector);
    printVector3(node.Vector, "Node Vector (Origin)");

    CoordinateConverter coordinateConverter;

    CartesianVector cartesianVec(node.Vector.x, node.Vector.y, node.Vector.z);
    printCartesianVector(cartesianVec, "Cartesian Vector (Origin)");

    SphericalVector spherical = coordinateConverter.cartesianToSpherical(cartesianVec);
    printSphericalVector(spherical, "Spherical Vector (Origin)");

    CartesianVector convertedCartesian = coordinateConverter.sphericalToCartesian(spherical);
    printCartesianVector(convertedCartesian, "Converted Cartesian Vector (Origin)");

    Vector3 convertedVector(convertedCartesian.x, convertedCartesian.y, convertedCartesian.z);
    printVector3(convertedVector, "Converted Vector (Origin)");

    EXPECT_NEAR(convertedVector.x, originalVector.x, EPSILON) << "X 좌표가 일치하지 않습니다.";
    EXPECT_NEAR(convertedVector.y, originalVector.y, EPSILON) << "Y 좌표가 일치하지 않습니다.";
    EXPECT_NEAR(convertedVector.z, originalVector.z, EPSILON) << "Z 좌표가 일치하지 않습니다.";
}

TEST(CoordinateConverterTest, AxisAlignedVectors) {
    CoordinateConverter coordinateConverter;

    // X축에 평행한 벡터
    Vector3 xVector(1.0f, 0.0f, 0.0f);
    printVector3(xVector, "Original Vector (X-Axis)");
    NodeVector nodeX(1, xVector);
    printVector3(nodeX.Vector, "Node Vector (X-Axis)");

    CartesianVector cartesianX(nodeX.Vector.x, nodeX.Vector.y, nodeX.Vector.z);
    printCartesianVector(cartesianX, "Cartesian Vector (X-Axis)");

    SphericalVector sphericalX = coordinateConverter.cartesianToSpherical(cartesianX);
    printSphericalVector(sphericalX, "Spherical Vector (X-Axis)");

    CartesianVector convertedCartesianX = coordinateConverter.sphericalToCartesian(sphericalX);
    printCartesianVector(convertedCartesianX, "Converted Cartesian Vector (X-Axis)");

    Vector3 convertedVectorX(convertedCartesianX.x, convertedCartesianX.y, convertedCartesianX.z);
    printVector3(convertedVectorX, "Converted Vector (X-Axis)");

    EXPECT_NEAR(convertedVectorX.x, xVector.x, EPSILON);
    EXPECT_NEAR(convertedVectorX.y, xVector.y, EPSILON);
    EXPECT_NEAR(convertedVectorX.z, xVector.z, EPSILON);

    std::cout << "\n"; // 구분을 위해 줄바꿈 추가

    // Y축에 평행한 벡터
    Vector3 yVector(0.0f, 1.0f, 0.0f);
    printVector3(yVector, "Original Vector (Y-Axis)");
    NodeVector nodeY(2, yVector);
    printVector3(nodeY.Vector, "Node Vector (Y-Axis)");

    CartesianVector cartesianY(nodeY.Vector.x, nodeY.Vector.y, nodeY.Vector.z);
    printCartesianVector(cartesianY, "Cartesian Vector (Y-Axis)");

    SphericalVector sphericalY = coordinateConverter.cartesianToSpherical(cartesianY);
    printSphericalVector(sphericalY, "Spherical Vector (Y-Axis)");

    CartesianVector convertedCartesianY = coordinateConverter.sphericalToCartesian(sphericalY);
    printCartesianVector(convertedCartesianY, "Converted Cartesian Vector (Y-Axis)");

    Vector3 convertedVectorY(convertedCartesianY.x, convertedCartesianY.y, convertedCartesianY.z);
    printVector3(convertedVectorY, "Converted Vector (Y-Axis)");

    EXPECT_NEAR(convertedVectorY.x, yVector.x, EPSILON);
    EXPECT_NEAR(convertedVectorY.y, yVector.y, EPSILON);
    EXPECT_NEAR(convertedVectorY.z, yVector.z, EPSILON);

    std::cout << "\n"; // 구분을 위해 줄바꿈 추가

    // Z축에 평행한 벡터
    Vector3 zVector(0.0f, 0.0f, 1.0f);
    printVector3(zVector, "Original Vector (Z-Axis)");
    NodeVector nodeZ(3, zVector);
    printVector3(nodeZ.Vector, "Node Vector (Z-Axis)");

    CartesianVector cartesianZ(nodeZ.Vector.x, nodeZ.Vector.y, nodeZ.Vector.z);
    printCartesianVector(cartesianZ, "Cartesian Vector (Z-Axis)");

    SphericalVector sphericalZ = coordinateConverter.cartesianToSpherical(cartesianZ);
    printSphericalVector(sphericalZ, "Spherical Vector (Z-Axis)");

    CartesianVector convertedCartesianZ = coordinateConverter.sphericalToCartesian(sphericalZ);
    printCartesianVector(convertedCartesianZ, "Converted Cartesian Vector (Z-Axis)");

    Vector3 convertedVectorZ(convertedCartesianZ.x, convertedCartesianZ.y, convertedCartesianZ.z);
    printVector3(convertedVectorZ, "Converted Vector (Z-Axis)");

    EXPECT_NEAR(convertedVectorZ.x, zVector.x, EPSILON);
    EXPECT_NEAR(convertedVectorZ.y, zVector.y, EPSILON);
    EXPECT_NEAR(convertedVectorZ.z, zVector.z, EPSILON);
}

TEST(CoordinateConverterTest, ArbitraryVectorConversion) {
    Vector3 originalVector(3.0f, 4.0f, 5.0f);
    printVector3(originalVector, "Original Vector (Arbitrary)");
    NodeVector node(4, originalVector);
    printVector3(node.Vector, "Node Vector (Arbitrary)");

    CoordinateConverter coordinateConverter;

    CartesianVector cartesianVec(node.Vector.x, node.Vector.y, node.Vector.z);
    printCartesianVector(cartesianVec, "Cartesian Vector (Arbitrary)");

    SphericalVector spherical = coordinateConverter.cartesianToSpherical(cartesianVec);
    printSphericalVector(spherical, "Spherical Vector (Arbitrary)");

    CartesianVector convertedCartesian = coordinateConverter.sphericalToCartesian(spherical);
    printCartesianVector(convertedCartesian, "Converted Cartesian Vector (Arbitrary)");

    Vector3 convertedVector(convertedCartesian.x, convertedCartesian.y, convertedCartesian.z);
    printVector3(convertedVector, "Converted Vector (Arbitrary)");

    EXPECT_NEAR(convertedVector.x, originalVector.x, EPSILON) << "X 좌표가 일치하지 않습니다.";
    EXPECT_NEAR(convertedVector.y, originalVector.y, EPSILON) << "Y 좌표가 일치하지 않습니다.";
    EXPECT_NEAR(convertedVector.z, originalVector.z, EPSILON) << "Z 좌표가 일치하지 않습니다.";
}
