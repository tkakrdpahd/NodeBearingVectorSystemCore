// ObjectManagerTest.cc

#include <gtest/gtest.h>
#include "ObjectManager.h"
#include "NodeVector.h"
#include "BearingVector.h"
#include "LinerSegment.h"
#include "Vector3.h"

// Test Fixture for ObjectManager
class ObjectManagerTest : public ::testing::Test {
protected:
    ObjectManager manager;
};

// Test NodeVector CRUD operations
TEST_F(ObjectManagerTest, NodeVectorCRUD) {
    // Create
    EXPECT_TRUE(manager.createNodeVector(1, Vector3(1.0f, 2.0f, 3.0f)));
    EXPECT_FALSE(manager.createNodeVector(1, Vector3(4.0f, 5.0f, 6.0f))); // Duplicate ID

    // Read
    auto node = manager.readNodeVector(1);
    ASSERT_TRUE(node.has_value());
    EXPECT_EQ(node->Index, 1);
    EXPECT_EQ(node->Vector, Vector3(1.0f, 2.0f, 3.0f));

    // Update
    EXPECT_TRUE(manager.updateNodeVector(1, Vector3(7.0f, 8.0f, 9.0f)));
    node = manager.readNodeVector(1);
    ASSERT_TRUE(node.has_value());
    EXPECT_EQ(node->Vector, Vector3(7.0f, 8.0f, 9.0f));

    // Delete
    EXPECT_TRUE(manager.deleteNodeVector(1));
    EXPECT_FALSE(manager.readNodeVector(1).has_value());
    EXPECT_FALSE(manager.deleteNodeVector(1)); // Already deleted
}

// Test BearingVector CRUD operations
TEST_F(ObjectManagerTest, BearingVectorCRUD) {
    // Create
    NodeVector node(1, Vector3(1.0f, 2.0f, 3.0f));
    EXPECT_TRUE(manager.createBearingVector(node, Vector3(0.1f, 0.2f, 0.3f), Vector3(5.0f, 0.0f, 0.0f)));
    EXPECT_FALSE(manager.createBearingVector(node, Vector3(0.4f, 0.5f, 0.6f), Vector3(5.0f, 0.0f, 0.0f))); // Duplicate Vector.x

    // Read
    auto bearing = manager.readBearingVector(5.0f);
    ASSERT_TRUE(bearing.has_value());
    EXPECT_EQ(bearing->Node.Index, 1);
    EXPECT_EQ(bearing->Vector.x, 5.0f);

    // Update
    EXPECT_TRUE(manager.updateBearingVector(5.0f, Vector3(0.7f, 0.8f, 0.9f)));
    bearing = manager.readBearingVector(5.0f);
    ASSERT_TRUE(bearing.has_value());
    EXPECT_EQ(bearing->Force, Vector3(0.7f, 0.8f, 0.9f));

    // Delete
    EXPECT_TRUE(manager.deleteBearingVector(5.0f));
    EXPECT_FALSE(manager.readBearingVector(5.0f).has_value());
    EXPECT_FALSE(manager.deleteBearingVector(5.0f)); // Already deleted
}

// Test LinerSegment operations
TEST_F(ObjectManagerTest, LinerSegmentOperations) {
    // Create LinerSegment
    NodeVector startNode(1, Vector3(0.0f, 0.0f, 0.0f));
    NodeVector endNode(2, Vector3(1.0f, 1.0f, 1.0f));
    std::vector<BearingVector> startBearing = { BearingVector(startNode, Vector3(0.0f, 0.0f, 1.0f), Vector3(0.1f, 0.1f, 0.1f)) };
    std::vector<BearingVector> endBearing = { BearingVector(endNode, Vector3(0.0f, 0.0f, -1.0f), Vector3(0.2f, 0.2f, 0.2f)) };

    EXPECT_TRUE(manager.createLinerSegment(startNode, startBearing, endNode, endBearing));

    // Read all LinerSegments
    auto linerSegments = manager.readAllLinerSegments();
    EXPECT_EQ(linerSegments.size(), 1);
    EXPECT_EQ(linerSegments[0].NodeStart.Index, 1);
    EXPECT_EQ(linerSegments[0].NodeEnd.Index, 2);

    // Delete LinerSegment
    EXPECT_TRUE(manager.deleteLinerSegment(startNode, endNode));
    linerSegments = manager.readAllLinerSegments();
    EXPECT_TRUE(linerSegments.empty());

    // Delete non-existing segment
    EXPECT_FALSE(manager.deleteLinerSegment(startNode, endNode));
}

// Test mixed operations
TEST_F(ObjectManagerTest, MixedOperations) {
    // Add NodeVectors
    EXPECT_TRUE(manager.createNodeVector(1, Vector3(1.0f, 2.0f, 3.0f)));
    EXPECT_TRUE(manager.createNodeVector(2, Vector3(4.0f, 5.0f, 6.0f)));

    // Add BearingVectors
    NodeVector node1(1, Vector3(1.0f, 2.0f, 3.0f));
    EXPECT_TRUE(manager.createBearingVector(node1, Vector3(0.1f, 0.2f, 0.3f), Vector3(5.0f, 0.0f, 0.0f)));

    // Add LinerSegment
    NodeVector node2(2, Vector3(4.0f, 5.0f, 6.0f));
    std::vector<BearingVector> bearingStart = { BearingVector(node1, Vector3(0.0f, 0.0f, 1.0f), Vector3(0.1f, 0.1f, 0.1f)) };
    std::vector<BearingVector> bearingEnd = { BearingVector(node2, Vector3(0.0f, 0.0f, -1.0f), Vector3(0.2f, 0.2f, 0.2f)) };

    EXPECT_TRUE(manager.createLinerSegment(node1, bearingStart, node2, bearingEnd));
    auto linerSegments = manager.readAllLinerSegments();
    EXPECT_EQ(linerSegments.size(), 1);

    // Cleanup
    EXPECT_TRUE(manager.deleteLinerSegment(node1, node2));
    EXPECT_TRUE(manager.deleteNodeVector(1));
    EXPECT_TRUE(manager.deleteNodeVector(2));
    EXPECT_TRUE(manager.deleteBearingVector(5.0f));
}
