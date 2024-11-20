// ObjectManagerTest.cc

#include <gtest/gtest.h>
#include "ObjectManager.h"
#include "NodeVector.h"
#include "BearingVector.h"
#include "LinearSegment.h"
#include "Vector3.h"

// Test Fixture for ObjectManager
class ObjectManagerTest : public ::testing::Test {
protected:
    ObjectManager manager;

    // SetUp 함수에서 필요한 초기화를 수행할 수 있습니다.
    void SetUp() override {
        // 필요한 경우 초기화 코드 추가
    }

    // TearDown 함수에서 필요한 정리를 수행할 수 있습니다.
    void TearDown() override {
        // 필요한 경우 정리 코드 추가
    }
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
    // 먼저 NodeVector를 생성해야 BearingVector를 추가할 수 있습니다.
    EXPECT_TRUE(manager.createNodeVector(1, Vector3(1.0f, 2.0f, 3.0f)));
    NodeVector node(1, Vector3(1.0f, 2.0f, 3.0f));

    // Create
    EXPECT_TRUE(manager.createBearingVector(node, Vector3(0.1f, 0.2f, 0.3f), Vector3(5.0f, 0.0f, 0.0f)));
    EXPECT_FALSE(manager.createBearingVector(node, Vector3(0.4f, 0.5f, 0.6f), Vector3(5.0f, 0.0f, 0.0f))); // Duplicate BearingVector for the same Node

    // Read
    auto bearing = manager.readBearingVector(node);
    ASSERT_TRUE(bearing.has_value());
    EXPECT_EQ(bearing->Node.Index, 1);
    EXPECT_EQ(bearing->Vector.x, 5.0f);

    // Update
    EXPECT_TRUE(manager.updateBearingVector(node, Vector3(0.7f, 0.8f, 0.9f)));
    bearing = manager.readBearingVector(node);
    ASSERT_TRUE(bearing.has_value());
    EXPECT_EQ(bearing->Force, Vector3(0.7f, 0.8f, 0.9f));

    // Delete
    EXPECT_TRUE(manager.deleteBearingVector(node));
    EXPECT_FALSE(manager.readBearingVector(node).has_value());
    EXPECT_FALSE(manager.deleteBearingVector(node)); // Already deleted
}

// Test LinearSegment operations
TEST_F(ObjectManagerTest, LinearSegmentOperations) {
    // Create NodeVectors
    EXPECT_TRUE(manager.createNodeVector(1, Vector3(0.0f, 0.0f, 0.0f)));
    EXPECT_TRUE(manager.createNodeVector(2, Vector3(1.0f, 1.0f, 1.0f)));
    NodeVector startNode(1, Vector3(0.0f, 0.0f, 0.0f));
    NodeVector endNode(2, Vector3(1.0f, 1.0f, 1.0f));

    // Create BearingVectors for LinearSegment
    EXPECT_TRUE(manager.createBearingVector(startNode, Vector3(0.0f, 0.0f, 1.0f), Vector3(0.1f, 0.1f, 0.1f)));
    EXPECT_TRUE(manager.createBearingVector(endNode, Vector3(0.0f, 0.0f, -1.0f), Vector3(0.2f, 0.2f, 0.2f)));
    
    std::vector<BearingVector> startBearing = { manager.readBearingVector(startNode).value() };
    std::vector<BearingVector> endBearing = { manager.readBearingVector(endNode).value() };

    // Create LinearSegment
    EXPECT_TRUE(manager.createLinearSegment(startNode, startBearing, endNode, endBearing));

    // Read all LinearSegments
    auto LinearSegments = manager.readAllLinearSegments();
    EXPECT_EQ(LinearSegments.size(), 1);
    EXPECT_EQ(LinearSegments[0].getStartNode().Index, 1);
    EXPECT_EQ(LinearSegments[0].getEndNode().Index, 2);

    // Delete LinearSegment
    EXPECT_TRUE(manager.deleteLinearSegment(startNode, endNode));
    LinearSegments = manager.readAllLinearSegments();
    EXPECT_TRUE(LinearSegments.empty());

    // Delete non-existing segment
    EXPECT_FALSE(manager.deleteLinearSegment(startNode, endNode));
}

// Test mixed operations
TEST_F(ObjectManagerTest, MixedOperations) {
    // Add NodeVectors
    EXPECT_TRUE(manager.createNodeVector(1, Vector3(1.0f, 2.0f, 3.0f)));
    EXPECT_TRUE(manager.createNodeVector(2, Vector3(4.0f, 5.0f, 6.0f)));
    NodeVector node1(1, Vector3(1.0f, 2.0f, 3.0f));
    NodeVector node2(2, Vector3(4.0f, 5.0f, 6.0f));

    // Add BearingVectors
    EXPECT_TRUE(manager.createBearingVector(node1, Vector3(0.1f, 0.2f, 0.3f), Vector3(5.0f, 0.0f, 0.0f)));
    EXPECT_TRUE(manager.createBearingVector(node2, Vector3(0.4f, 0.5f, 0.6f), Vector3(6.0f, 0.0f, 0.0f)));

    // Add LinearSegment
    std::vector<BearingVector> bearingStart = { manager.readBearingVector(node1).value() };
    std::vector<BearingVector> bearingEnd = { manager.readBearingVector(node2).value() };

    EXPECT_TRUE(manager.createLinearSegment(node1, bearingStart, node2, bearingEnd));
    auto LinearSegments = manager.readAllLinearSegments();
    EXPECT_EQ(LinearSegments.size(), 1);

    // Cleanup
    EXPECT_TRUE(manager.deleteLinearSegment(node1, node2));
    EXPECT_TRUE(manager.deleteBearingVector(node1));
    EXPECT_TRUE(manager.deleteBearingVector(node2));
    EXPECT_TRUE(manager.deleteNodeVector(1));
    EXPECT_TRUE(manager.deleteNodeVector(2));
}
