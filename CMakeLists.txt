cmake_minimum_required(VERSION 3.20)
project(NodeBearingVectorSystem VERSION 0.1 LANGUAGES CXX)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ----------------------------
# vcpkg 설정
# ----------------------------
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    message(FATAL_ERROR "CMAKE_TOOLCHAIN_FILE must be set to the vcpkg toolchain file.")
endif()

# ----------------------------
# 종속성 패키지 찾기
# ----------------------------
find_package(CURL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(Drogon CONFIG REQUIRED)
find_package(Vulkan REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

# ----------------------------
# 소스 파일 수집
# ----------------------------
file(GLOB_RECURSE SOURCES
    "modules/*.cpp"
    "services/*.cpp"
)

# ----------------------------
# 라이브러리 추가
# ----------------------------
add_library(NodeBearingVectorSystemLib STATIC ${SOURCES})

# 헤더 파일 경로 설정
target_include_directories(NodeBearingVectorSystemLib PUBLIC
    ${PROJECT_SOURCE_DIR}/modules/entities
    ${PROJECT_SOURCE_DIR}/modules/operators
    ${PROJECT_SOURCE_DIR}/modules/segments
    ${PROJECT_SOURCE_DIR}/modules/vectors

    ${PROJECT_SOURCE_DIR}/services/server
    ${PROJECT_SOURCE_DIR}/services/managers
)

# 링크 라이브러리 설정
target_link_libraries(NodeBearingVectorSystemLib PUBLIC
    CURL::libcurl
    nlohmann_json::nlohmann_json
    Drogon::Drogon
    Vulkan::Vulkan
    SDL2::SDL2
    SDL2::SDL2main
    OpenGL::GL
    imgui::imgui
)

# 플랫폼 별 설정
if (APPLE)
    find_library(METAL_LIBRARY Metal)
    if (METAL_LIBRARY)
        target_link_libraries(NodeBearingVectorSystemLib PRIVATE ${METAL_LIBRARY})
    else()
        message(WARNING "Metal framework not found on macOS. This may impact rendering performance.")
    endif()
endif()

# ----------------------------
# 실행 파일 추가
# ----------------------------
add_executable(${PROJECT_NAME} main.cpp)

# 메인 실행 파일에 라이브러리 연결
target_link_libraries(${PROJECT_NAME} PRIVATE NodeBearingVectorSystemLib)

# -------------------------------
# Add tests subdirectory
# -------------------------------
add_subdirectory(tests)
