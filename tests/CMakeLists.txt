# ----------------------------
# Google Test
# ----------------------------
enable_testing()

# 테스트 실행 파일 추가
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
    GTest::gtest_main # gtest_main만 링크
    NodeBearingVectorSystemLib
)

# 자동으로 테스트 등록 및 실행
include(GoogleTest)
gtest_discover_tests(test_nodebearingvectorsystem)
