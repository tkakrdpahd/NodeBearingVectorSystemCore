// BearingVectorTest.cc

#include <gtest/gtest.h>
#include "Vector3.h"
#include "NodeVector.h"
#include "BearingVector.h"
#include <sstream>

TEST(BearingVectorTest, Constructor) {
    Vector3 nodeVec(1.0f, 2.0f, 3.0f);
    NodeVector node(5, nodeVec);
    Vector3 force(4.0f, 5.0f, 6.0f);
    Vector3 bearingVec(7.0f, 8.0f, 9.0f);
    BearingVector bv(node, force, bearingVec);
    EXPECT_EQ(bv.Node.Index, 5);
    EXPECT_FLOAT_EQ(bv.Node.Vector.x, 1.0f);
    EXPECT_FLOAT_EQ(bv.Node.Vector.y, 2.0f);
    EXPECT_FLOAT_EQ(bv.Node.Vector.z, 3.0f);
    EXPECT_FLOAT_EQ(bv.Force.x, 4.0f);
    EXPECT_FLOAT_EQ(bv.Force.y, 5.0f);
    EXPECT_FLOAT_EQ(bv.Force.z, 6.0f);
    EXPECT_FLOAT_EQ(bv.Vector.x, 7.0f);
    EXPECT_FLOAT_EQ(bv.Vector.y, 8.0f);
    EXPECT_FLOAT_EQ(bv.Vector.z, 9.0f);
}

TEST(BearingVectorTest, OutputOperator) {
    Vector3 nodeVec(1.0f, 2.0f, 3.0f);
    NodeVector node(5, nodeVec);
    Vector3 force(4.0f, 5.0f, 6.0f);
    Vector3 bearingVec(7.0f, 8.0f, 9.0f);
    BearingVector bv(node, force, bearingVec);
    std::ostringstream oss;
    oss << bv;
    EXPECT_EQ(oss.str(), "BearingVector(Node: NodeVector(Index: 5, Vector: (1, 2, 3)), Force: (4, 5, 6), Vector: (7, 8, 9))");
}
