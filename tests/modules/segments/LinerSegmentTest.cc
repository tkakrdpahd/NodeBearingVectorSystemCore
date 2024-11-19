// LinerSegmentTest.cc

#include <gtest/gtest.h>
#include <cmath> // for std::abs
#include <iostream> // for std::cout

#include "Vector3.h"
#include "CoordinateConverter.h" // Ensure this header exists and is correctly implemented
#include "NodeVector.h"
#include "BearingVector.h"
#include "LinearSegment.h"

// Test fixture for LinerSegment
class LinerSegmentTest : public ::testing::Test {
protected:
    // SetUp is called before each test
    void SetUp() override {
        // Initialize start node
        startNode = new NodeVector(1, Vector3(1.0f, 0.0f, 0.0f)); // Index=1, Position=(1, 0, 0)

        // Initialize start bearings
        BearingVector bv1(*startNode, Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f));
        BearingVectorStart.push_back(bv1);

        // Initialize end node
        endNode = new NodeVector(2, Vector3(0.0f, 1.0f, 0.0f)); // Index=2, Position=(0, 1, 0)

        // Initialize end bearings
        BearingVector bv2(*endNode, Vector3(0.0f, 0.0f, -1.0f), Vector3(0.0f, 0.0f, -1.0f));
        BearingVectorEnd.push_back(bv2);

        // Create LinerSegment
        segment = new LinerSegment(*startNode, BearingVectorStart, *endNode, BearingVectorEnd);
    }

    // TearDown is called after each test
    void TearDown() override {
        delete segment;
        delete endNode;
        delete startNode;
    }

    // Members accessible to all tests
    NodeVector* startNode;
    NodeVector* endNode;
    std::vector<BearingVector> BearingVectorStart;
    std::vector<BearingVector> BearingVectorEnd;
    LinerSegment* segment;
};

// Test the creation of LinerSegment
TEST_F(LinerSegmentTest, CreationTest) {
    EXPECT_EQ(segment->NodeStart.Index, 1);
    EXPECT_EQ(segment->NodeEnd.Index, 2);
    EXPECT_EQ(segment->BearingVectorStart.size(), 1);
    EXPECT_EQ(segment->BearingVectorEnd.size(), 1);
}

// Test control points calculation
TEST_F(LinerSegmentTest, ControlPointsTest) {
    // Assuming alpha = 0.5
    float alpha = 0.5f;
    std::vector<Vector3> controlPoints = segment->CalculateControlPoints(alpha);

    // Expected control points:
    // P0 = (1,0,0)
    // P1 = P0 + B1 * F1 = (1,0,0) + (0,0,1) * (0,0,1) = (1,0,1)
    // P2 = alpha * (P1) + (1 - alpha) * (P3) = 0.5*(1,0,1) + 0.5*(0,1,1) = (0.5,0.5,1)
    // P3 = N2.Vector - B2 * F2 = (0,1,0) - (0,0,-1)*1 = (0,1,1)
    // P4 = N2.Vector = (0,1,0)

    std::vector<Vector3> expectedControlPoints = {
        Vector3(1.0f, 0.0f, 0.0f), // P0
        Vector3(1.0f, 0.0f, 1.0f), // P1
        Vector3(0.5f, 0.5f, 1.0f), // P2
        Vector3(0.0f, 1.0f, 1.0f), // P3
        Vector3(0.0f, 1.0f, 0.0f)  // P4
    };

    ASSERT_EQ(controlPoints.size(), expectedControlPoints.size());

    for (size_t i = 0; i < controlPoints.size(); ++i) {
        EXPECT_NEAR(controlPoints[i].x, expectedControlPoints[i].x, 1e-5);
        EXPECT_NEAR(controlPoints[i].y, expectedControlPoints[i].y, 1e-5);
        EXPECT_NEAR(controlPoints[i].z, expectedControlPoints[i].z, 1e-5);
    }
}

// Test B-Spline creation
TEST_F(LinerSegmentTest, BSplineCreationTest) {
    float alpha = 0.5f;
    int numSegments = 100;

    segment->CreateBSpline(alpha, numSegments);

    // Expected points using the Bezier curve defined by control points:
    // P0 = (1,0,0)
    // P1 = (1,0,1)
    // P2 = (0.5,0.5,1)
    // P3 = (0,1,1)
    // P4 = (0,1,0)

    // For numSegments=100, t=0.0, 0.01, ...,1.0
    // Here, we just check the number of points
    EXPECT_EQ(segment->GetLinerSegmentCache()->size(), static_cast<size_t>(numSegments + 1));
}

// Test Polygon Vertices creation
TEST_F(LinerSegmentTest, PolygonVerticesTest) {
    float alpha = 0.5f;
    int numSegments = 100;
    int lod = 10;

    segment->CreateBSpline(alpha, numSegments);
    std::vector<Vector3> polygonVertices = segment->CreatePolygonVertices(lod);

    // Expected number of polygon vertices: lod + 1 (since last point is always included)
    // But avoid duplicate if last point is already included
    EXPECT_EQ(polygonVertices.size(), static_cast<size_t>(lod + 1));
}

// Test Curvature calculation
TEST_F(LinerSegmentTest, CurvatureTest) {
    float alpha = 0.5f;
    int numSegments = 100;
    segment->CreateBSpline(alpha, numSegments);

    // Test curvature at t=0.5
    float t = 0.5f;
    float curvature = segment->CalculateCurvature(t);

    // For the given control points, curvature should be positive
    EXPECT_GT(curvature, 0.0f);
}

// Test Vector3 operations
TEST(Vector3Test, HadamardProductTest) {
    Vector3 v1(1.0f, 2.0f, 3.0f);
    Vector3 v2(4.0f, 5.0f, 6.0f);

    Vector3 expected(4.0f, 10.0f, 18.0f);
    Vector3 result = v1 * v2;

    EXPECT_NEAR(result.x, expected.x, 1e-5);
    EXPECT_NEAR(result.y, expected.y, 1e-5);
    EXPECT_NEAR(result.z, expected.z, 1e-5);
}
