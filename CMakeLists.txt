cmake_minimum_required(VERSION 3.20)
project(Template VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

# Ensure Vcpkg toolchain is used
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Set paths for Glad and GLFW
set(GLAD_INC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include")
set(GLFW_LIB_NAME "external/glfw")
set(GLFW_INC_PATH ${GLFW_LIB_NAME}/include)

# Configure GLFW build settings (if building from source)
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL        OFF CACHE BOOL "" FORCE)

# Add GLFW as a subdirectory (optional)
add_subdirectory(${GLFW_LIB_NAME})

# Glob all source files
file(GLOB SOURCES
    "src/*.cpp"
    "test/*.cpp"
    "src/ui/*.cpp"
    "src/utils/*.cpp"
    "external/glad/src/glad.c"
)

# ImGui source files and headers
set(IMGUI_LIB_NAME "external/imgui")

set(IMGUI_SOURCES
    "${IMGUI_LIB_NAME}/imgui.cpp"
    "${IMGUI_LIB_NAME}/imgui_demo.cpp"
    "${IMGUI_LIB_NAME}/imgui_draw.cpp"
    "${IMGUI_LIB_NAME}/imgui_widgets.cpp"
    "${IMGUI_LIB_NAME}/imgui_tables.cpp"
    "${IMGUI_LIB_NAME}/backends/imgui_impl_glfw.cpp"
    "${IMGUI_LIB_NAME}/backends/imgui_impl_opengl3.cpp"
)

set(IMGUI_HEADERS
    "${IMGUI_LIB_NAME}/imconfig.h"
    "${IMGUI_LIB_NAME}/imgui.h"
    "${IMGUI_LIB_NAME}/imgui_internal.h"
    "${IMGUI_LIB_NAME}/imstb_rectpack.h"
    "${IMGUI_LIB_NAME}/imstb_textedit.h"
    "${IMGUI_LIB_NAME}/imstb_truetype.h"
    "${IMGUI_LIB_NAME}/backends/imgui_impl_glfw.h"
    "${IMGUI_LIB_NAME}/backends/imgui_impl_opengl3.h"
)

# Create ImGui library
add_library(ImGui STATIC
    ${IMGUI_SOURCES}
    ${IMGUI_HEADERS}
)

# Add ImGui compile definitions
target_compile_definitions(ImGui
    PRIVATE
        IMGUI_IMPL_OPENGL_LOADER_GLAD=1
)

# Set include directories for ImGui
target_include_directories(ImGui
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/external
        "${IMGUI_INC_PATH}"
        "${GLFW_INC_PATH}"
        "${GLAD_INC_PATH}"
)

# Find required packages (doctest, Intl, and OpenGL)
find_package(doctest CONFIG REQUIRED)
find_package(Intl REQUIRED)
find_package(OpenGL REQUIRED)

# Create executable
add_executable(myTemplate ${SOURCES})

# Set include directories for the main project
target_include_directories(myTemplate
    PUBLIC
        ${GLAD_INC_PATH}
        "${PROJECT_SOURCE_DIR}/src"
        "${PROJECT_SOURCE_DIR}/src/include"
        "${PROJECT_SOURCE_DIR}/src/ui"
        "${PROJECT_SOURCE_DIR}/src/utils"
        "${PROJECT_SOURCE_DIR}/test"
)

# Link libraries (glfw, ImGui, OpenGL)
target_link_libraries(myTemplate
    PUBLIC
        glfw
        ImGui
        OpenGL::GL
    PRIVATE
        Intl::Intl
        doctest::doctest
)
