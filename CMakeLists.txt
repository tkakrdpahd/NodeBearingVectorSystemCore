# Minimum CMake version
cmake_minimum_required(VERSION 3.12)

# Project setup
project(NodeBearingVectorSystem VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find package
find_package(yaml-cpp REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# Sources (CMake 3.12 and above support ** for recursive globbing)
file(GLOB_RECURSE SOURCES
    "main.cpp"
    "modules/*.cpp"
    "modules/**/*.cpp"
)

# 필요한 ImGui 백엔드 파일만 포함
set(IMGUI_BACKEND_SOURCES
    # Essential module
    ${PROJECT_SOURCE_DIR}/imgui/imgui.cpp
    ${PROJECT_SOURCE_DIR}/imgui/imgui_widgets.cpp
    ${PROJECT_SOURCE_DIR}/imgui/imgui_tables.cpp
    ${PROJECT_SOURCE_DIR}/imgui/imgui_draw.cpp
    ${PROJECT_SOURCE_DIR}/imgui/imgui_demo.cpp
    # OpenGL
    ${PROJECT_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.cpp
    ${PROJECT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES} ${IMGUI_BACKEND_SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE

    #${PROJECT_SOURCE_DIR}/modules
    ${PROJECT_SOURCE_DIR}/modules/entities
    ${PROJECT_SOURCE_DIR}/modules/operators
    ${PROJECT_SOURCE_DIR}/modules/segments
    ${PROJECT_SOURCE_DIR}/modules/vectors

    #${PROJECT_SOURCE_DIR}/server
    ${PROJECT_SOURCE_DIR}/server/api
    ${PROJECT_SOURCE_DIR}/server/dto
    ${PROJECT_SOURCE_DIR}/server/managers

    #${PROJECT_SOURCE_DIR}/services
    ${PROJECT_SOURCE_DIR}/services/interfaces
    ${PROJECT_SOURCE_DIR}/services/managers
)

# Link yaml-cpp library using the correct target name
target_link_libraries(${PROJECT_NAME} PRIVATE
    yaml-cpp::yaml-cpp
    OpenGL::GL
    glfw
)

# Find and link Vulkan
find_package(Vulkan REQUIRED)
if (Vulkan_FOUND)
    message(STATUS "Vulkan found: ${Vulkan_INCLUDE_DIR}")
    target_include_directories(${PROJECT_NAME} PRIVATE ${Vulkan_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)
endif()

# Find and link OpenGL
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    message(STATUS "OpenGL found: ${OPENGL_INCLUDE_DIR}")
    target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
endif()

# Find and link Metal (macOS only)
if (APPLE)
    find_library(METAL_LIBRARY Metal)
    if (METAL_LIBRARY)
        message(STATUS "Metal found: ${METAL_LIBRARY}")
        target_link_libraries(${PROJECT_NAME} PRIVATE ${METAL_LIBRARY})
        
        # Suppress missing include directory warnings
        target_compile_options(${PROJECT_NAME} PRIVATE -Wno-error -Wno-missing-include-dirs)
    endif()
endif()

# Find and link DirectX (Windows only)
if (WIN32)
    find_library(D3D11_LIBRARY d3d11)
    find_library(DXGI_LIBRARY dxgi)
    if (D3D11_LIBRARY AND DXGI_LIBRARY)
        message(STATUS "DirectX found: ${D3D11_LIBRARY}, ${DXGI_LIBRARY}")
        target_link_libraries(${PROJECT_NAME} PRIVATE ${D3D11_LIBRARY} ${DXGI_LIBRARY})
    endif()
endif()
