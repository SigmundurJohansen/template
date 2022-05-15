cmake_minimum_required(VERSION 3.1)
project(Template VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
add_subdirectory(external/doctest)

file(GLOB SOURCES 
    "src/*.cpp", "*.cpp", "*/*.cpp", "*/*/*.cpp",  
    "*.h", "*/*.h", "*/*/*.h"
)

add_library(${PROJECT_NAME} ${SOURCES} 
            "../include/"
            "src/"
            )

target_include_directories(${PROJECT_NAME} 
            PUBLIC
            "${PROJECT_SOURCE_DIR}/src"
            "${PROJECT_SOURCE_DIR}/src/include/"
            "${PROJECT_SOURCE_DIR}/src/tests/"
            )

include_directories(${DOCTEST_INCLUDE_DIR})


add_executable(myTemplate ${SOURCES} ) #include/tests/hello_test.cc)

target_link_libraries(myTemplate doctest)

