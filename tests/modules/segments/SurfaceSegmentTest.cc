// SurfaceSegmentTest.cc

#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include "SurfaceSegment.h"
#include "NodeVector.h"
#include "BearingVector.h"

// Test fixture for SurfaceSegment
class SurfaceSegmentTest : public ::testing::Test {
protected:
    // SetUp is called before each test
    void SetUp() override {
        // Initialize test nodes
        nodes = std::make_shared<std::vector<NodeVector>>();
        nodes->emplace_back(1, Vector3(0.0f, 0.0f, 0.0f)); // Node 1
        nodes->emplace_back(2, Vector3(1.0f, 1.0f, 1.0f)); // Node 2

        // Initialize test bearings
        bearings = std::make_shared<std::vector<BearingVector>>();
        bearings->emplace_back(NodeVector(1, Vector3(0.0f, 0.0f, 0.0f)), Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
        bearings->emplace_back(NodeVector(2, Vector3(1.0f, 1.0f, 1.0f)), Vector3(1.0f, 0.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));

        // Create a SurfaceSegment
        segment = std::make_unique<SurfaceSegment>();
    }

    // TearDown is called after each test
    void TearDown() override {
        // Cleanup resources
        segment.reset();
    }

    // Members accessible to all tests
    std::shared_ptr<std::vector<NodeVector>> nodes;
    std::shared_ptr<std::vector<BearingVector>> bearings;
    std::unique_ptr<SurfaceSegment> segment;
};

// Test SurfaceSegment creation
TEST_F(SurfaceSegmentTest, CreateSurfaceSegment) {
    EXPECT_TRUE(segment->CreateSurfaceSegment());
    EXPECT_TRUE(segment->isSegmentValid());
}

// Test SurfaceSegment read functionality
TEST_F(SurfaceSegmentTest, ReadSurfaceSegment) {
    segment->CreateSurfaceSegment();
    EXPECT_TRUE(segment->ReadSurfaceSegment());

    // Invalidate and try reading again
    segment->invalidate();
    EXPECT_FALSE(segment->ReadSurfaceSegment());
}

// Test SurfaceSegment update functionality
TEST_F(SurfaceSegmentTest, UpdateSurfaceSegment) {
    segment->CreateSurfaceSegment();

    // Update the segment and ensure validity
    EXPECT_TRUE(segment->UpdateSurfaceSegment());
    EXPECT_TRUE(segment->isSegmentValid());

    // Invalidate and try updating
    segment->invalidate();
    EXPECT_FALSE(segment->UpdateSurfaceSegment());
}

// Test SurfaceSegment deletion
TEST_F(SurfaceSegmentTest, DeleteSurfaceSegment) {
    segment->CreateSurfaceSegment();

    EXPECT_TRUE(segment->DeleteSurfaceSegment());
    EXPECT_TRUE(segment->isSegmentValid());

    // Try deleting already invalid segment
    segment->invalidate();
    EXPECT_FALSE(segment->DeleteSurfaceSegment());
}

// Test isValid state changes
TEST_F(SurfaceSegmentTest, IsValidStateChanges) {
    segment->CreateSurfaceSegment();
    EXPECT_TRUE(segment->isSegmentValid());

    // Invalidate the segment and check
    segment->invalidate();
    EXPECT_FALSE(segment->isSegmentValid());

    // Revalidate the segment
    segment->CreateSurfaceSegment();
    EXPECT_TRUE(segment->isSegmentValid());
}

// Test setting and getting segment attributes
TEST_F(SurfaceSegmentTest, SetAndGetAttributes) {
    // Test setting and getting index
    segment->setIndex(10);
    EXPECT_EQ(segment->getIndex(), 10);

    // Test setting and getting LOD
    segment->setLOD(5);
    EXPECT_EQ(segment->getLOD(), 5);
}

// Test node and bearing accessors
TEST_F(SurfaceSegmentTest, NodeAndBearingAccessors) {
    auto testNodes = segment->getNodes();
    auto testBearings = segment->getBearings();

    EXPECT_NE(testNodes, nullptr);
    EXPECT_NE(testBearings, nullptr);

    // Ensure they are initially empty
    EXPECT_TRUE(testNodes->empty());
    EXPECT_TRUE(testBearings->empty());

    // Populate nodes and bearings and validate access
    testNodes->push_back(NodeVector(1, Vector3(0.0f, 0.0f, 0.0f)));
    testBearings->push_back(BearingVector(NodeVector(1, Vector3(0.0f, 0.0f, 0.0f)), Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f)));

    EXPECT_EQ(testNodes->size(), 1);
    EXPECT_EQ(testBearings->size(), 1);
}
