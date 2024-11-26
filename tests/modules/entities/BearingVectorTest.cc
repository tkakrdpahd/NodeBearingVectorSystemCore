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

TEST(BearingVectorTest, JsonSerialization) {
    // Create initial object
    Vector3 nodeVec(1.0f, 2.0f, 3.0f);
    NodeVector node(5, nodeVec);
    Vector3 force(4.0f, 5.0f, 6.0f);
    Vector3 bearingVec(7.0f, 8.0f, 9.0f);
    BearingVector original(node, force, bearingVec);

    // Serialize to JSON
    json j = original.toJson();

    // Verify JSON structure
    EXPECT_EQ(j["node"]["index"], 5);
    EXPECT_FLOAT_EQ(j["node"]["vector"]["x"], 1.0f);
    EXPECT_FLOAT_EQ(j["node"]["vector"]["y"], 2.0f);
    EXPECT_FLOAT_EQ(j["node"]["vector"]["z"], 3.0f);
    EXPECT_FLOAT_EQ(j["force"]["x"], 4.0f);
    EXPECT_FLOAT_EQ(j["force"]["y"], 5.0f);
    EXPECT_FLOAT_EQ(j["force"]["z"], 6.0f);
    EXPECT_FLOAT_EQ(j["vector"]["x"], 7.0f);
    EXPECT_FLOAT_EQ(j["vector"]["y"], 8.0f);
    EXPECT_FLOAT_EQ(j["vector"]["z"], 9.0f);

    // Deserialize
    BearingVector deserialized = BearingVector::fromJson(j);

    // Verify deserialized object
    EXPECT_EQ(deserialized.Node.Index, original.Node.Index);
    EXPECT_FLOAT_EQ(deserialized.Node.Vector.x, original.Node.Vector.x);
    EXPECT_FLOAT_EQ(deserialized.Node.Vector.y, original.Node.Vector.y);
    EXPECT_FLOAT_EQ(deserialized.Node.Vector.z, original.Node.Vector.z);
    EXPECT_FLOAT_EQ(deserialized.Force.x, original.Force.x);
    EXPECT_FLOAT_EQ(deserialized.Force.y, original.Force.y);
    EXPECT_FLOAT_EQ(deserialized.Force.z, original.Force.z);
    EXPECT_FLOAT_EQ(deserialized.Vector.x, original.Vector.x);
    EXPECT_FLOAT_EQ(deserialized.Vector.y, original.Vector.y);
    EXPECT_FLOAT_EQ(deserialized.Vector.z, original.Vector.z);
}

TEST(BearingVectorTest, JsonSerializationString) {
    Vector3 nodeVec(1.0f, 2.0f, 3.0f);
    NodeVector node(5, nodeVec);
    Vector3 force(4.0f, 5.0f, 6.0f);
    Vector3 bearingVec(7.0f, 8.0f, 9.0f);
    BearingVector bv(node, force, bearingVec);
    
    // Serialize to JSON string
    json j = bv.toJson();
    std::string jsonStr = j.dump();

    // Deserialize from JSON string
    json parsedJson = json::parse(jsonStr);
    BearingVector deserialized = BearingVector::fromJson(parsedJson);

    // Verify
    EXPECT_EQ(deserialized.Node.Index, 5);
    EXPECT_FLOAT_EQ(deserialized.Node.Vector.x, 1.0f);
    EXPECT_FLOAT_EQ(deserialized.Node.Vector.y, 2.0f);
    EXPECT_FLOAT_EQ(deserialized.Node.Vector.z, 3.0f);
    EXPECT_FLOAT_EQ(deserialized.Force.x, 4.0f);
    EXPECT_FLOAT_EQ(deserialized.Force.y, 5.0f);
    EXPECT_FLOAT_EQ(deserialized.Force.z, 6.0f);
    EXPECT_FLOAT_EQ(deserialized.Vector.x, 7.0f);
    EXPECT_FLOAT_EQ(deserialized.Vector.y, 8.0f);
    EXPECT_FLOAT_EQ(deserialized.Vector.z, 9.0f);
}
