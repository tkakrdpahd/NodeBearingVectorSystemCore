// VertexTest.cc

#include <gtest/gtest.h>
#include "Vertex.h"
#include "NodeVector.h"     // NodeVector를 사용하기 위해 포함
#include "BearingVector.h"  // BearingVector를 사용하기 위해 포함
#include <memory>
#include <functional>

// Helper 구조체 및 함수: stdout과 stderr를 모두 캡처
struct CapturedOutput {
    std::string stdout_output;
    std::string stderr_output;
};

CapturedOutput CaptureOutput(std::function<void()> func) {
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    func();
    CapturedOutput output;
    output.stdout_output = testing::internal::GetCapturedStdout();
    output.stderr_output = testing::internal::GetCapturedStderr();
    return output;
}

TEST(VertexTest, ConstructorInitializesCorrectly) {
    Vertex vertex;
    EXPECT_NO_THROW(vertex.ReadNodeVector());
    EXPECT_NO_THROW(vertex.GetBearingVector());
}

TEST(VertexTest, CreateAndUpdateNodeVector) {
    Vertex vertex;

    // NodeVector 업데이트 및 값 확인
    NodeVector newNode(1, Vector3(1.0f, 2.0f, 3.0f));
    vertex.UpdateNodeVector(newNode);

    CapturedOutput output = CaptureOutput([&vertex]() {
        vertex.ReadNodeVector();
    });

    // "Index: 1"과 "Vector: (1, 2, 3)"가 stdout 또는 stderr에 존재하는지 확인
    bool found_index = output.stdout_output.find("Index: 1") != std::string::npos ||
                       output.stderr_output.find("Index: 1") != std::string::npos;
    bool found_vector = output.stdout_output.find("Vector: (1, 2, 3)") != std::string::npos ||
                        output.stderr_output.find("Vector: (1, 2, 3)") != std::string::npos;

    EXPECT_TRUE(found_index);
    EXPECT_TRUE(found_vector);
}

TEST(VertexTest, AddAndReadBearingVectors) {
    Vertex vertex;

    // BearingVector 추가
    NodeVector node0(0, Vector3(0.0f, 0.0f, 0.0f)); // BearingVector에 필요한 NodeVector
    BearingVector bearing1(node0, Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 2.0f));
    BearingVector bearing2(node0, Vector3(0.0f, 1.0f, 0.0f), Vector3(3.0f, 4.0f, 5.0f));

    vertex.PostBearingVector(bearing1);
    vertex.PostBearingVector(bearing2);

    CapturedOutput output = CaptureOutput([&vertex]() {
        vertex.GetBearingVector();
    });

    // "Vector: (0, 1, 2)"과 "Vector: (3, 4, 5)"가 stdout 또는 stderr에 존재하는지 확인
    bool found_bearing1 = output.stdout_output.find("Vector: (0, 1, 2)") != std::string::npos ||
                           output.stderr_output.find("Vector: (0, 1, 2)") != std::string::npos;
    bool found_bearing2 = output.stdout_output.find("Vector: (3, 4, 5)") != std::string::npos ||
                           output.stderr_output.find("Vector: (3, 4, 5)") != std::string::npos;

    EXPECT_TRUE(found_bearing1);
    EXPECT_TRUE(found_bearing2);
}

TEST(VertexTest, UpdateAndDeleteBearingVectors) {
    Vertex vertex;

    // BearingVector 추가
    NodeVector node0(0, Vector3(0.0f, 0.0f, 0.0f));
    BearingVector bearing(node0, Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 2.0f));
    vertex.PostBearingVector(bearing);

    // BearingVector 업데이트
    BearingVector newBearing(node0, Vector3(0.0f, 0.0f, 1.0f), Vector3(7.0f, 8.0f, 9.0f));
    vertex.PutBearingVector(newBearing);

    CapturedOutput updateOutput = CaptureOutput([&vertex]() {
        vertex.GetBearingVector();
    });

    // "Vector: (7, 8, 9)"가 stdout 또는 stderr에 존재하는지 확인
    bool found_new_bearing = updateOutput.stdout_output.find("Vector: (7, 8, 9)") != std::string::npos ||
                             updateOutput.stderr_output.find("Vector: (7, 8, 9)") != std::string::npos;
    EXPECT_TRUE(found_new_bearing);

    // BearingVector 삭제
    vertex.DeleteBearingVector();

    CapturedOutput deleteOutput = CaptureOutput([&vertex]() {
        vertex.GetBearingVector();
    });

    // "BearingVectorList is empty or not initialized."가 stdout 또는 stderr에 존재하는지 확인
    bool found_empty_list = deleteOutput.stdout_output.find("BearingVectorList is empty or not initialized.") != std::string::npos ||
                            deleteOutput.stderr_output.find("BearingVectorList is empty or not initialized.") != std::string::npos;
    EXPECT_TRUE(found_empty_list);
}

TEST(VertexTest, DeleteNodeVector) {
    Vertex vertex;

    // NodeVector 업데이트
    NodeVector newNode(1, Vector3(1.0f, 2.0f, 3.0f));
    vertex.UpdateNodeVector(newNode);

    // NodeVector 삭제 (FRIEND_TEST을 통해 접근 가능)
    vertex.DeleteNodeVector();

    CapturedOutput output = CaptureOutput([&vertex]() {
        vertex.ReadNodeVector();
    });

    // "NodeVector is not initialized."가 stdout 또는 stderr에 존재하는지 확인
    bool found_not_initialized = output.stdout_output.find("NodeVector is not initialized.") != std::string::npos ||
                                 output.stderr_output.find("NodeVector is not initialized.") != std::string::npos;
    EXPECT_TRUE(found_not_initialized);
}

TEST(VertexTest, BearingVectorListLifecycle) {
    Vertex vertex;

    // BearingVector 추가
    NodeVector node0(0, Vector3(0.0f, 0.0f, 0.0f));
    BearingVector bearing(node0, Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 2.0f));
    vertex.PostBearingVector(bearing);

    // BearingVector 삭제
    vertex.DeleteBearingVector();

    CapturedOutput output = CaptureOutput([&vertex]() {
        vertex.GetBearingVector();
    });

    // "BearingVectorList is empty or not initialized."가 stdout 또는 stderr에 존재하는지 확인
    bool found_empty_list = output.stdout_output.find("BearingVectorList is empty or not initialized.") != std::string::npos ||
                            output.stderr_output.find("BearingVectorList is empty or not initialized.") != std::string::npos;
    EXPECT_TRUE(found_empty_list);
}
