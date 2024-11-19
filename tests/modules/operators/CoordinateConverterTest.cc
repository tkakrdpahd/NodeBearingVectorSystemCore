// CoordinateConverterTest.cc

#include <gtest/gtest.h>
#include <cmath>
#include "CoordinateConverter.h"

/**
 * @brief Float 비교를 위한 허용 오차.
 */
constexpr float kTolerance = 1e-5;

/**
 * @brief Cartesian to Spherical 변환 테스트.
 */
TEST(CoordinateConverterTest, CartesianToSphericalTest) {
    // 입력: 단위 벡터 (x, y, z)
    CartesianVector cartesianVector(1.0f, 1.0f, 1.0f);
    auto result = CoordinateConverter::cartesianToSpherical(cartesianVector);

    // 기대 결과
    float expectedR = std::sqrt(1.0f + 1.0f + 1.0f);
    float expectedTheta = std::atan2(1.0f, 1.0f);
    float expectedPhi = std::acos(1.0f / expectedR);

    // 검증
    EXPECT_NEAR(result.r, expectedR, kTolerance);
    EXPECT_NEAR(result.theta, expectedTheta, kTolerance);
    EXPECT_NEAR(result.phi, expectedPhi, kTolerance);
}

/**
 * @brief Spherical to Cartesian 변환 테스트.
 */
TEST(CoordinateConverterTest, SphericalToCartesianTest) {
    // 입력: 반지름과 각도 (r, theta, phi)
    SphericalVector sphericalVector(1.0f, M_PI / 4, M_PI / 4);
    auto result = CoordinateConverter::sphericalToCartesian(sphericalVector);

    // 기대 결과
    float expectedX = std::sin(M_PI / 4) * std::cos(M_PI / 4);
    float expectedY = std::sin(M_PI / 4) * std::sin(M_PI / 4);
    float expectedZ = std::cos(M_PI / 4);

    // 검증
    EXPECT_NEAR(result.x, expectedX, kTolerance);
    EXPECT_NEAR(result.y, expectedY, kTolerance);
    EXPECT_NEAR(result.z, expectedZ, kTolerance);
}

/**
 * @brief Round-trip 변환 테스트 (Cartesian -> Spherical -> Cartesian).
 */
TEST(CoordinateConverterTest, RoundTripCartesianToSphericalToCartesian) {
    CartesianVector cartesianVector(3.0f, 4.0f, 5.0f);

    // Round-trip 변환
    auto spherical = CoordinateConverter::cartesianToSpherical(cartesianVector);
    auto cartesianResult = CoordinateConverter::sphericalToCartesian(spherical);

    // 검증
    EXPECT_NEAR(cartesianVector.x, cartesianResult.x, kTolerance);
    EXPECT_NEAR(cartesianVector.y, cartesianResult.y, kTolerance);
    EXPECT_NEAR(cartesianVector.z, cartesianResult.z, kTolerance);
}

/**
 * @brief Round-trip 변환 테스트 (Spherical -> Cartesian -> Spherical).
 */
TEST(CoordinateConverterTest, RoundTripSphericalToCartesianToSpherical) {
    SphericalVector sphericalVector(2.0f, M_PI / 6, M_PI / 3);

    // Round-trip 변환
    auto cartesian = CoordinateConverter::sphericalToCartesian(sphericalVector);
    auto sphericalResult = CoordinateConverter::cartesianToSpherical(cartesian);

    // 검증
    EXPECT_NEAR(sphericalVector.r, sphericalResult.r, kTolerance);
    EXPECT_NEAR(sphericalVector.theta, sphericalResult.theta, kTolerance);
    EXPECT_NEAR(sphericalVector.phi, sphericalResult.phi, kTolerance);
}
