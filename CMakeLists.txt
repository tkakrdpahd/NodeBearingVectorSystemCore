# Minimum CMake version
cmake_minimum_required(VERSION 3.12)

# Project setup
project(NodeBearingVectorSystem VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find yaml-cpp package
find_package(yaml-cpp REQUIRED)

# Sources (CMake 3.12 and above support ** for recursive globbing)
file(GLOB_RECURSE SOURCES
    "main.cpp"
    "module/*.cpp"
    "module/**/*.cpp"
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/module
    ${PROJECT_SOURCE_DIR}/module/Operators
    ${PROJECT_SOURCE_DIR}/module/Vectors
    ${PROJECT_SOURCE_DIR}/module/Segments
    ${PROJECT_SOURCE_DIR}/module/Server
    ${PROJECT_SOURCE_DIR}/module/imgui
)

# Link yaml-cpp library using the correct target name
target_link_libraries(${PROJECT_NAME} PRIVATE
    yaml-cpp::yaml-cpp
)
