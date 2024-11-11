# Minimum CMake version
cmake_minimum_required(VERSION 3.12)

# Project setup
project(TheNewDream VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Sources (CMake 3.12 이상에서 ** 사용 가능)
file(GLOB_RECURSE SOURCES "main.cpp" "module/*.cpp" "module/**/*.cpp")

# Add executable
add_executable(NodeBearingVectorSystem ${SOURCES})

# Include directories
target_include_directories(NodeBearingVectorSystem PRIVATE
    ${PROJECT_SOURCE_DIR}/module
    ${PROJECT_SOURCE_DIR}/module/Operators
    ${PROJECT_SOURCE_DIR}/module/Vectors
    ${PROJECT_SOURCE_DIR}/module/Server
)
