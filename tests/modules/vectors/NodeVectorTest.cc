/**
 * NodeVectorTest.cc
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 7, 2024
 * Last Modified: Nov 13, 2024
 * 
 * Purpose of Class:
 * NodeVectorTest
 */

#include <gtest/gtest.h>
#include <sstream>
#include "Vector3.h"
#include "NodeVector.h"

// 사용자 정의 매처: Vector3의 각 성분을 개별적으로 비교 (근사값)
::testing::AssertionResult CompareVector3Near(const Vector3& lhs, const Vector3& rhs, float epsilon = 1e-5f) {
    if (std::abs(lhs.x - rhs.x) > epsilon ||
        std::abs(lhs.y - rhs.y) > epsilon ||
        std::abs(lhs.z - rhs.z) > epsilon) {
        return ::testing::AssertionFailure() << "Vectors are not approximately equal: (" 
                                             << lhs.x << ", " << lhs.y << ", " << lhs.z 
                                             << ") vs (" 
                                             << rhs.x << ", " << rhs.y << ", " << rhs.z 
                                             << ")";
    }
    return ::testing::AssertionSuccess();
}

// 매처를 사용하는 매크로 정의
#define EXPECT_VECTOR_NEAR(lhs, rhs, epsilon) EXPECT_TRUE(CompareVector3Near(lhs, rhs, epsilon))

// 테스트 1: 생성자가 올바르게 작동하는지 확인
TEST(NodeVectorTest, ConstructorTest) {
    int testIndex = 5;
    Vector3 testVector(1.0f, 2.0f, 3.0f);
    NodeVector node(testIndex, testVector);

    EXPECT_EQ(node.index, testIndex);
    EXPECT_VECTOR_NEAR(node.vector, testVector, 1e-5f); // 근사값 비교
}

// 테스트 2: operator<< 오버로딩이 올바르게 작동하는지 확인
TEST(NodeVectorTest, OutputOperatorTest) {
    int testIndex = 10;
    Vector3 testVector(4.5f, 5.5f, 6.5f);
    NodeVector node(testIndex, testVector);

    std::stringstream ss;
    ss << node;

    std::string expectedOutput = "Index: 10, Vector: (4.5, 5.5, 6.5)";
    EXPECT_EQ(ss.str(), expectedOutput);
}

// 추가 테스트: NodeVector 객체 간의 비교
TEST(NodeVectorTest, EqualityTest) {
    int index1 = 1;
    Vector3 vec1(1.0f, 1.0f, 1.0f);
    NodeVector node1(index1, vec1);

    int index2 = 1;
    Vector3 vec2(1.0f, 1.0f, 1.0f);
    NodeVector node2(index2, vec2);

    EXPECT_EQ(node1.index, node2.index);
    EXPECT_VECTOR_NEAR(node1.vector, node2.vector, 1e-5f); // 근사값 비교
}

// main 함수: 모든 테스트를 실행
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
