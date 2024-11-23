# Root CMakeLists.txt
cmake_minimum_required(VERSION 3.14)
project(NodeBearingVectorSystem VERSION 0.1 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ----------------------------
# Find required dependencies
# ----------------------------
find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(Drogon REQUIRED)

# Required Packages for GUI
find_package(Vulkan REQUIRED)
find_package(SDL2 REQUIRED)

# ------------------------------
# Include GoogleTest submodule
# ------------------------------
add_subdirectory(external/googletest)

# ---------------------------
# Collect source files
# ---------------------------
file(GLOB_RECURSE SOURCES
    "modules/*.cpp"
    "services/*.cpp"
    "services/**/*.cpp"
)

# ---------------------------
# Include ImGui sources directly
# ---------------------------
set(IMGUI_SOURCES
    ${PROJECT_SOURCE_DIR}/external/imgui-master/imgui.cpp
    ${PROJECT_SOURCE_DIR}/external/imgui-master/imgui_widgets.cpp
    ${PROJECT_SOURCE_DIR}/external/imgui-master/imgui_tables.cpp
    ${PROJECT_SOURCE_DIR}/external/imgui-master/imgui_draw.cpp
    ${PROJECT_SOURCE_DIR}/external/imgui-master/imgui_demo.cpp

    # Vulkan & SDL2 backends setting for imgui
    ${PROJECT_SOURCE_DIR}/external/imgui-master/backends/imgui_impl_sdl2.cpp
    ${PROJECT_SOURCE_DIR}/external/imgui-master/backends/imgui_impl_vulkan.cpp
)

# Create a library from the sources
add_library(NodeBearingVectorSystemLib ${SOURCES} ${IMGUI_SOURCES})

# ----------------
# Include headers
# ----------------
target_include_directories(NodeBearingVectorSystemLib PUBLIC
    ${PROJECT_SOURCE_DIR}/external/imgui-master
    ${PROJECT_SOURCE_DIR}/external/imgui-master/backends

    ${PROJECT_SOURCE_DIR}/modules/entities
    ${PROJECT_SOURCE_DIR}/modules/operators
    ${PROJECT_SOURCE_DIR}/modules/segments
    ${PROJECT_SOURCE_DIR}/modules/vectors

    ${PROJECT_SOURCE_DIR}/services/server
    ${PROJECT_SOURCE_DIR}/services/managers
)

# Link libraries
target_link_libraries(NodeBearingVectorSystemLib PUBLIC
    CURL::libcurl
    nlohmann_json::nlohmann_json
    Drogon::Drogon

    SDL2::SDL2
    SDL2::SDL2main
    Vulkan::Vulkan
)

# Platform-specific libraries
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

# -------------------------------
# Add the main executable
# -------------------------------
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE NodeBearingVectorSystemLib)

# -------------------------------
# Add tests subdirectory
# -------------------------------
add_subdirectory(tests)
