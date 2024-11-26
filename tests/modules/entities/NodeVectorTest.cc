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

TEST(NodeVectorTest, JsonSerialization) {
    // 초기 객체 생성
    Vector3 v(1.0f, 2.0f, 3.0f);
    NodeVector original(5, v);

    // 직렬화
    json j = original.toJson();

    // JSON 구조 검증
    EXPECT_EQ(j["index"], 5);
    EXPECT_FLOAT_EQ(j["vector"]["x"], 1.0f);
    EXPECT_FLOAT_EQ(j["vector"]["y"], 2.0f);
    EXPECT_FLOAT_EQ(j["vector"]["z"], 3.0f);

    // 역직렬화
    NodeVector deserialized = NodeVector::fromJson(j);

    // 역직렬화된 객체 검증
    EXPECT_EQ(deserialized.Index, original.Index);
    EXPECT_FLOAT_EQ(deserialized.Vector.x, original.Vector.x);
    EXPECT_FLOAT_EQ(deserialized.Vector.y, original.Vector.y);
    EXPECT_FLOAT_EQ(deserialized.Vector.z, original.Vector.z);
}

TEST(NodeVectorTest, JsonSerializationString) {
    Vector3 v(1.0f, 2.0f, 3.0f);
    NodeVector node(5, v);
    
    // JSON 문자열로 직렬화
    json j = node.toJson();
    std::string jsonStr = j.dump();

    // JSON 문자열에서 역직렬화
    json parsedJson = json::parse(jsonStr);
    NodeVector deserialized = NodeVector::fromJson(parsedJson);

    // 검증
    EXPECT_EQ(deserialized.Index, 5);
    EXPECT_FLOAT_EQ(deserialized.Vector.x, 1.0f);
    EXPECT_FLOAT_EQ(deserialized.Vector.y, 2.0f);
    EXPECT_FLOAT_EQ(deserialized.Vector.z, 3.0f);
}