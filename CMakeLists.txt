# Root CMakeLists.txt
cmake_minimum_required(VERSION 3.14)
project(NodeBearingVectorSystem VERSION 0.1 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} main.cpp)