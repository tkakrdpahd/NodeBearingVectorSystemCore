# tests/CMakeLists.txt

# --------------------
# Google Test Setting
# --------------------
# 이미 googletest는 루트 CMakeLists.txt에서 add_subdirectory 했으므로, 여기서는 추가하지 않습니다.

enable_testing()

# Add the test executable
add_executable(test_nodebearingvectorsystem 
  modules/entities/Vector3Test.cc
  modules/entities/NodeVectorTest.cc
  modules/entities/BearingVectorTest.cc
  modules/operators/CoordinateConverterTest.cc
  modules/segments/LinearSegmentTest.cc
)

# Include directories
target_include_directories(test_nodebearingvectorsystem PRIVATE
    ${PROJECT_SOURCE_DIR}/modules/entities
    ${PROJECT_SOURCE_DIR}/modules/operators
    ${PROJECT_SOURCE_DIR}/modules/segments
    ${PROJECT_SOURCE_DIR}/modules/vectors
)

# Link against GTest와 메인 라이브러리
target_link_libraries(test_nodebearingvectorsystem PRIVATE
    gtest
    gtest_main
    NodeBearingVectorSystemLib
)

# 자동으로 테스트를 등록하고 실행되도록 설정
include(GoogleTest)
gtest_discover_tests(test_nodebearingvectorsystem)
