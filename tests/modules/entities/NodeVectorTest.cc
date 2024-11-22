// NodeVectorTest.cc

#include <gtest/gtest.h>
#include "Vector3.h"
#include "NodeVector.h"
#include <sstream>

TEST(NodeVectorTest, Constructor) {
    Vector3 v(1.0f, 2.0f, 3.0f);
    NodeVector node(5, v);
    EXPECT_EQ(node.Index, 5);
    EXPECT_FLOAT_EQ(node.Vector.x, 1.0f);
    EXPECT_FLOAT_EQ(node.Vector.y, 2.0f);
    EXPECT_FLOAT_EQ(node.Vector.z, 3.0f);
}

TEST(NodeVectorTest, OutputOperator) {
    Vector3 v(1.0f, 2.0f, 3.0f);
    NodeVector node(5, v);
    std::ostringstream oss;
    oss << node;
    EXPECT_EQ(oss.str(), "NodeVector(Index: 5, Vector: (1, 2, 3))");
}
