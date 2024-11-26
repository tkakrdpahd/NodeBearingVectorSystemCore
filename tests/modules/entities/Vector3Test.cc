// Vector3Test.cc

#include <gtest/gtest.h>
#include "Vector3.h"

TEST(Vector3Test, DefaultConstructor) {
    Vector3 v;
    EXPECT_FLOAT_EQ(v.x, 0.0f);
    EXPECT_FLOAT_EQ(v.y, 0.0f);
    EXPECT_FLOAT_EQ(v.z, 0.0f);
}

TEST(Vector3Test, ParameterizedConstructor) {
    Vector3 v(1.0f, 2.0f, 3.0f);
    EXPECT_FLOAT_EQ(v.x, 1.0f);
    EXPECT_FLOAT_EQ(v.y, 2.0f);
    EXPECT_FLOAT_EQ(v.z, 3.0f);
}

TEST(Vector3Test, Addition) {
    Vector3 v1(1.0f, 2.0f, 3.0f);
    Vector3 v2(4.0f, 5.0f, 6.0f);
    Vector3 result = v1 + v2;
    EXPECT_FLOAT_EQ(result.x, 5.0f);
    EXPECT_FLOAT_EQ(result.y, 7.0f);
    EXPECT_FLOAT_EQ(result.z, 9.0f);
}

TEST(Vector3Test, Subtraction) {
    Vector3 v1(5.0f, 7.0f, 9.0f);
    Vector3 v2(1.0f, 2.0f, 3.0f);
    Vector3 result = v1 - v2;
    EXPECT_FLOAT_EQ(result.x, 4.0f);
    EXPECT_FLOAT_EQ(result.y, 5.0f);
    EXPECT_FLOAT_EQ(result.z, 6.0f);
}

TEST(Vector3Test, ScalarMultiplication) {
    Vector3 v(1.0f, 2.0f, 3.0f);
    float scalar = 2.0f;
    Vector3 result = v * scalar;
    EXPECT_FLOAT_EQ(result.x, 2.0f);
    EXPECT_FLOAT_EQ(result.y, 4.0f);
    EXPECT_FLOAT_EQ(result.z, 6.0f);
}

TEST(Vector3Test, ScalarDivision) {
    Vector3 v(2.0f, 4.0f, 6.0f);
    float scalar = 2.0f;
    Vector3 result = v / scalar;
    EXPECT_FLOAT_EQ(result.x, 1.0f);
    EXPECT_FLOAT_EQ(result.y, 2.0f);
    EXPECT_FLOAT_EQ(result.z, 3.0f);
}

TEST(Vector3Test, DotProduct) {
    Vector3 v1(1.0f, 0.0f, 0.0f);
    Vector3 v2(0.0f, 1.0f, 0.0f);
    float result = v1.dot(v2);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

TEST(Vector3Test, CrossProduct) {
    Vector3 v1(1.0f, 0.0f, 0.0f);
    Vector3 v2(0.0f, 1.0f, 0.0f);
    Vector3 result = v1.cross(v2);
    EXPECT_FLOAT_EQ(result.x, 0.0f);
    EXPECT_FLOAT_EQ(result.y, 0.0f);
    EXPECT_FLOAT_EQ(result.z, 1.0f);
}

TEST(Vector3Test, Magnitude) {
    Vector3 v(3.0f, 4.0f, 0.0f);
    float result = v.magnitude();
    EXPECT_FLOAT_EQ(result, 5.0f);
}

TEST(Vector3Test, Normalized) {
    Vector3 v(0.0f, 3.0f, 4.0f);
    Vector3 result = v.normalized();
    EXPECT_NEAR(result.x, 0.0f, 1e-5f);
    EXPECT_NEAR(result.y, 0.6f, 1e-5f);
    EXPECT_NEAR(result.z, 0.8f, 1e-5f);
}

TEST(Vector3Test, EqualityOperator) {
    Vector3 v1(1.000001f, 2.000001f, 3.000001f);
    Vector3 v2(1.000002f, 2.000002f, 3.000002f);
    EXPECT_TRUE(v1 == v2);
}

TEST(Vector3Test, InequalityOperator) {
    Vector3 v1(1.0f, 2.0f, 3.0f);
    Vector3 v2(1.0f, 2.0f, 3.1f);
    EXPECT_TRUE(v1 != v2);
}

TEST(Vector3Test, IsZero) {
    Vector3 v(1e-6f, -1e-6f, 1e-6f);
    EXPECT_TRUE(v.isZero());
}

TEST(Vector3Test, Distance) {
    Vector3 v1(1.0f, 2.0f, 3.0f);
    Vector3 v2(4.0f, 6.0f, 3.0f);
    float dist = v1.distance(v2);
    EXPECT_FLOAT_EQ(dist, 5.0f);
}

TEST(Vector3Test, IndexOperator) {
    Vector3 v(1.0f, 2.0f, 3.0f);
    EXPECT_FLOAT_EQ(v[0], 1.0f);
    EXPECT_FLOAT_EQ(v[1], 2.0f);
    EXPECT_FLOAT_EQ(v[2], 3.0f);
}

TEST(Vector3Test, ScalarMultiplicationLeft) {
    Vector3 v(1.0f, 2.0f, 3.0f);
    float scalar = 2.0f;
    Vector3 result = scalar * v;
    EXPECT_FLOAT_EQ(result.x, 2.0f);
    EXPECT_FLOAT_EQ(result.y, 4.0f);
    EXPECT_FLOAT_EQ(result.z, 6.0f);
}

TEST(Vector3Test, Serialization) {
    Vector3 v(1.0f, 2.0f, 3.0f);
    json j = v.toJson();
    EXPECT_FLOAT_EQ(j["x"], 1.0f);
    EXPECT_FLOAT_EQ(j["y"], 2.0f);
    EXPECT_FLOAT_EQ(j["z"], 3.0f);
}

TEST(Vector3Test, Deserialization) {
    json j = { {"x", 4.0f}, {"y", 5.0f}, {"z", 6.0f} };
    Vector3 v = Vector3::fromJson(j);
    EXPECT_FLOAT_EQ(v.x, 4.0f);
    EXPECT_FLOAT_EQ(v.y, 5.0f);
    EXPECT_FLOAT_EQ(v.z, 6.0f);
}
