# tests/CMakeLists.txt

# --------------------
# Google Test Setting
# --------------------
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Add the test executable
add_executable(test_nodebearingvectorsystem 
  modules/vectors/NodeVectorTest.cc
)

# Link against GTest and the main library
target_link_libraries(test_nodebearingvectorsystem 
    GTest::gtest_main 
    NodeBearingVectorSystemLib
)

include(GoogleTest)
gtest_discover_tests(test_nodebearingvectorsystem)