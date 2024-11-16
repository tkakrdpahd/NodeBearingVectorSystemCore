#include "LinerSegment.h"
#include "NodeVector.h"
#include "BearingVector.h"
#include "Vector3.h"
#include "gtest/gtest.h"

// Test the SamplingBezierCurve method of LinerSegment
TEST(LinerSegmentTest, SamplingBezierCurveTest) {
    // Set up start and end nodes
    NodeVector startNode(1, Vector3(0.0, 0.0, 0.0));
    NodeVector endNode(2, Vector3(10.0, 10.0, 0.0));

    // Set up bearing vectors for start and end nodes using emplace_back to reduce copies
    std::vector<BearingVector> startBearingVectors;
    startBearingVectors.emplace_back(1, startNode, Vector3(1.0, 2.0, 0.0), Vector3(1.0, 0.0, 0.0));
    startBearingVectors.emplace_back(2, startNode, Vector3(2.0, 3.0, 0.0), Vector3(2.0, 1.0, 0.0));

    std::vector<BearingVector> endBearingVectors;
    endBearingVectors.emplace_back(3, endNode, Vector3(-1.0, -1.0, 0.0), Vector3(-1.0, 0.0, 0.0));
    endBearingVectors.emplace_back(4, endNode, Vector3(-2.0, -3.0, 0.0), Vector3(-2.0, -1.0, 0.0));

    // Create LinerSegment instance
    LinerSegment linerSegment(startNode, startBearingVectors, endNode, endBearingVectors);

    // Call the SamplingBezierCurve method (output will be checked manually)
    testing::internal::CaptureStdout();
    linerSegment.SamplingBezierCurve();
    std::string output = testing::internal::GetCapturedStdout();

    // Check if output is not empty
    ASSERT_FALSE(output.empty());
}

// Test the SamplingVertex method of LinerSegment
TEST(LinerSegmentTest, SamplingVertexTest) {
    // Set up start and end nodes
    NodeVector startNode(1, Vector3(0.0, 0.0, 0.0));
    NodeVector endNode(2, Vector3(10.0, 10.0, 0.0));

    // Set up bearing vectors for start and end nodes
    std::vector<BearingVector> startBearingVectors;
    startBearingVectors.push_back(BearingVector(1, startNode, Vector3(1.0, 2.0, 0.0), Vector3(1.0, 0.0, 0.0)));
    startBearingVectors.push_back(BearingVector(2, startNode, Vector3(2.0, 3.0, 0.0), Vector3(2.0, 1.0, 0.0)));

    std::vector<BearingVector> endBearingVectors;
    endBearingVectors.push_back(BearingVector(3, endNode, Vector3(-1.0, -1.0, 0.0), Vector3(-1.0, 0.0, 0.0)));
    endBearingVectors.push_back(BearingVector(4, endNode, Vector3(-2.0, -3.0, 0.0), Vector3(-2.0, -1.0, 0.0)));

    // Create LinerSegment instance
    LinerSegment linerSegment(startNode, startBearingVectors, endNode, endBearingVectors);

    // Call the SamplingVertex method (output will be checked manually)
    testing::internal::CaptureStdout();
    linerSegment.SamplingVertex();
    std::string output = testing::internal::GetCapturedStdout();

    // Check if output contains the expected message
    ASSERT_NE(output.find("Sampling vertices based on LOD"), std::string::npos);
}
