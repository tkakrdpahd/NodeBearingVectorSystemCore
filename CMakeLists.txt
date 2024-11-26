# Root CMakeLists.txt
cmake_minimum_required(VERSION 3.20)
project(NodeBearingVectorSystem VERSION 0.1 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ----------------------------
# vcpkg configuration
# ----------------------------
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    message(FATAL_ERROR "CMAKE_TOOLCHAIN_FILE must be set to the vcpkg toolchain file.")
endif()

# ----------------------------
# Find dependency packages
# ----------------------------

# API
find_package(nlohmann_json CONFIG REQUIRED)
find_package(Drogon CONFIG REQUIRED)

# GUI
find_package(imgui CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Vulkan REQUIRED)
find_package(SDL2 CONFIG REQUIRED)

# GTest
find_package(GTest CONFIG REQUIRED)

# ----------------------------
# Collect source files
# ----------------------------
file(GLOB_RECURSE SOURCES
    "modules/*.cpp"
    "services/*.cpp"
    "server/*.cpp"
)

# ----------------------------
# Add library
# ----------------------------
add_library(NodeBearingVectorSystemLib STATIC ${SOURCES})

# Set header file paths
target_include_directories(NodeBearingVectorSystemLib PUBLIC
    ${PROJECT_SOURCE_DIR}/modules/entities
    ${PROJECT_SOURCE_DIR}/modules/operators
    ${PROJECT_SOURCE_DIR}/modules/segments
    ${PROJECT_SOURCE_DIR}/modules/vectors

    ${PROJECT_SOURCE_DIR}/services/process
    ${PROJECT_SOURCE_DIR}/services/interface
    ${PROJECT_SOURCE_DIR}/services/managers

    ${PROJECT_SOURCE_DIR}/server
    ${PROJECT_SOURCE_DIR}/server/api
    ${PROJECT_SOURCE_DIR}/server/dto
    ${PROJECT_SOURCE_DIR}/server/managers
)

# Set link libraries
target_link_libraries(NodeBearingVectorSystemLib PUBLIC

    # API
    nlohmann_json::nlohmann_json
    Drogon::Drogon

    # GUI
    imgui::imgui
    OpenGL::GL
    Vulkan::Vulkan
    SDL2::SDL2
    SDL2::SDL2main
)

# Platform-specific configuration
if (APPLE)
    find_library(METAL_LIBRARY Metal)
    if (METAL_LIBRARY)
        target_link_libraries(NodeBearingVectorSystemLib PRIVATE ${METAL_LIBRARY})
        target_compile_options(NodeBearingVectorSystemLib PRIVATE -Wno-error -Wno-missing-include-dirs)
    endif()
endif()

if (WIN32)
    find_library(D3D11_LIBRARY d3d11)
    find_library(DXGI_LIBRARY dxgi)
    if (D3D11_LIBRARY AND DXGI_LIBRARY)
        target_link_libraries(NodeBearingVectorSystemLib PRIVATE ${D3D11_LIBRARY} ${DXGI_LIBRARY})
    endif()
endif()

# ----------------------------
# Add executable
# ----------------------------
add_executable(${PROJECT_NAME} main.cpp)

# Link library to the main executable
target_link_libraries(${PROJECT_NAME} PRIVATE NodeBearingVectorSystemLib)

# -------------------------------
# Add tests subdirectory
# -------------------------------
add_subdirectory(tests)
