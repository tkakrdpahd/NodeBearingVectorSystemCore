// LinearSegmentTest.cc

#include <gtest/gtest.h>
#include <cmath> // for std::abs
#include <memory> // for smart pointers
#include <iostream> // for std::cout

#include "Vector3.h"
#include "CoordinateConverter.h" // Ensure this header exists and is correctly implemented
#include "NodeVector.h"
#include "BearingVector.h"
#include "LinearSegment.h"

// Test fixture for LinearSegment
class LinearSegmentTest : public ::testing::Test {
protected:
    // SetUp is called before each test
    void SetUp() override {
        // Initialize start node
        startNode = std::make_unique<NodeVector>(1, Vector3(1.0f, 0.0f, 0.0f)); // Index=1, Position=(1, 0, 0)

        // Initialize start bearings
        BearingVector bv1(*startNode, Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f));
        BearingVectorStart.push_back(bv1);

        // Initialize end node
        endNode = std::make_unique<NodeVector>(2, Vector3(0.0f, 1.0f, 0.0f)); // Index=2, Position=(0, 1, 0)

        // Initialize end bearings
        BearingVector bv2(*endNode, Vector3(0.0f, 0.0f, -1.0f), Vector3(0.0f, 0.0f, -1.0f));
        BearingVectorEnd.push_back(bv2);

        // Create LinearSegment with default alpha and numSegments
        segment = std::make_unique<LinearSegment>(*startNode, BearingVectorStart, *endNode, BearingVectorEnd);
    }

    // TearDown is called after each test
    void TearDown() override {
        // Smart pointers automatically clean up
    }

    // Members accessible to all tests
    std::unique_ptr<NodeVector> startNode;
    std::unique_ptr<NodeVector> endNode;
    std::vector<BearingVector> BearingVectorStart;
    std::vector<BearingVector> BearingVectorEnd;
    std::unique_ptr<LinearSegment> segment;
};

// Test the creation of LinearSegment
TEST_F(LinearSegmentTest, CreationTest) {
    EXPECT_EQ(segment->getStartNode().Index, 1);
    EXPECT_EQ(segment->getEndNode().Index, 2);
    
    // Assuming NodeVector has a public member 'Vector' of type Vector3
    EXPECT_TRUE(segment->getStartNode().Vector == Vector3(1.0f, 0.0f, 0.0f));
    EXPECT_TRUE(segment->getEndNode().Vector == Vector3(0.0f, 1.0f, 0.0f));
    
    // Since LinearSegment does not have getBearingVectorStart and getBearingVectorEnd,
    // we cannot directly test their sizes unless we add such getters.
    // Alternatively, if BearingVectorStart and BearingVectorEnd are public,
    // you can access them directly (not recommended).
    
    // For now, we will skip testing BearingVector sizes
}

// Test control points calculation
TEST_F(LinearSegmentTest, ControlPointsTest) {
    // Access the CalculateControlPoints method
    // Note: Since CalculateControlPoints is private, we need to make it accessible for testing.
    // One approach is to use a friend test class or modify the class to expose it conditionally.
    // For simplicity, let's assume we have modified LinearSegment to make CalculateControlPoints public for testing purposes.
    // Alternatively, you can remove this test or test indirectly through public methods.

    // For demonstration, assuming CalculateControlPoints is public
    // If not, consider making it public or using friend testing

    // Assuming alpha = 0.5
    float alpha = 0.5f;
    std::vector<Vector3> controlPoints = segment->CalculateControlPoints(alpha);

    // Expected control points:
    // P0 = (1,0,0)
    // P1 = P0 + B1 * F1 = (1,0,0) + (0,0,1) * 1 = (1,0,1)
    // P2 = alpha * (P1) + (1 - alpha) * (P3) = 0.5*(1,0,1) + 0.5*(0,1,1) = (0.5,0.5,1)
    // P3 = N2.Vector + B2 * F2 = (0,1,0) + (0,0,-1) * (-1) = (0,1,1)
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
        EXPECT_NEAR(controlPoints[i].x, expectedControlPoints[i].x, 1e-5) << "Mismatch at control point " << i;
        EXPECT_NEAR(controlPoints[i].y, expectedControlPoints[i].y, 1e-5) << "Mismatch at control point " << i;
        EXPECT_NEAR(controlPoints[i].z, expectedControlPoints[i].z, 1e-5) << "Mismatch at control point " << i;
    }
}

// Test B-Spline creation
TEST_F(LinearSegmentTest, BSplineCreationTest) {
    // In the updated class, CreateBSpline() uses member variables alpha and numSegments
    // By default, alpha = 0.5f and numSegments = 100

    segment->CreateBSpline();

    // Expected number of points: numSegments + 1 = 101
    ASSERT_NE(segment->GetLinearSegmentCache(), nullptr);
    EXPECT_EQ(segment->GetLinearSegmentCache()->size(), static_cast<size_t>(100 + 1));
}

// Test Polygon Vertices creation
TEST_F(LinearSegmentTest, PolygonVerticesTest) {
    // In the updated class, CreateBSpline() uses member variables alpha and numSegments
    // By default, alpha = 0.5f and numSegments = 100
    // LOD = 1 initially

    // Set LOD to 10 for testing
    segment->SetLOD(10);

    // Create B-Spline
    segment->CreateBSpline();

    // Create Polygon Vertices
    std::vector<Vector3> polygonVertices = segment->CreatePolygonVertices(segment->ReadLOD());

    // Expected number of polygon vertices: LOD + 1 = 11
    EXPECT_EQ(polygonVertices.size(), static_cast<size_t>(10 + 1));
}

// Test Curvature calculation
TEST_F(LinearSegmentTest, CurvatureTest) {
    // Create B-Spline with default alpha and numSegments
    segment->CreateBSpline();

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

// Additional Tests to Cover Automatic Updates

// Test automatic B-Spline creation upon setting alpha
TEST_F(LinearSegmentTest, AutomaticBSplineOnAlphaUpdate) {
    // Capture the initial cache size
    size_t initialCacheSize = segment->GetLinearSegmentCache()->size();

    // Update alpha
    segment->SetAlpha(0.7f);

    // After updating alpha, CreateBSpline() should have been called
    // and the cache should be updated accordingly
    size_t updatedCacheSize = segment->GetLinearSegmentCache()->size();

    // Cache size should remain the same (numSegments + 1)
    EXPECT_EQ(initialCacheSize, updatedCacheSize);
}

// Test automatic B-Spline creation upon setting numSegments
TEST_F(LinearSegmentTest, AutomaticBSplineOnNumSegmentsUpdate) {
    // Update numSegments to 200
    segment->SetNumSegments(200);

    // After updating numSegments, CreateBSpline() should have been called
    // and the cache size should now be 201
    EXPECT_EQ(segment->GetLinearSegmentCache()->size(), static_cast<size_t>(200 + 1));
}

// Test automatic B-Spline creation upon setting start node
TEST_F(LinearSegmentTest, AutomaticBSplineOnStartNodeUpdate) {
    // Update start node
    NodeVector newStartNode(3, Vector3(2.0f, 0.0f, 0.0f));
    segment->SetStartNode(newStartNode);

    // After updating start node, CreateBSpline() should have been called
    // and the cache should be updated accordingly
    // Here, we can check the first point in the cache
    EXPECT_TRUE((*segment->GetLinearSegmentCache())[0] == Vector3(2.0f, 0.0f, 0.0f));
}

// Test automatic B-Spline creation upon setting end node
TEST_F(LinearSegmentTest, AutomaticBSplineOnEndNodeUpdate) {
    // Update end node
    NodeVector newEndNode(4, Vector3(0.0f, 2.0f, 0.0f));
    segment->SetEndNode(newEndNode);

    // After updating end node, CreateBSpline() should have been called
    // and the cache should be updated accordingly
    // Here, we can check the last point in the cache
    EXPECT_TRUE(segment->GetLinearSegmentCache()->back() == Vector3(0.0f, 2.0f, 0.0f));
}
