cmake_minimum_required(VERSION 3.5)
project(Template VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/build/)


add_executable(Template src/main.cpp)