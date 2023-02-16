cmake_minimum_required(VERSION 3.1)
project(Template VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
add_subdirectory(external/doctest)

file(GLOB SOURCES 
    "src/*.cpp", "test/*.cpp"
)

add_library(${PROJECT_NAME} ${SOURCES} 
            "src/"
            )

target_include_directories(${PROJECT_NAME} 
            PUBLIC
            "${PROJECT_SOURCE_DIR}/src"
            "${PROJECT_SOURCE_DIR}/src/include/"
            "${PROJECT_SOURCE_DIR}/test/"
            )

include_directories(${DOCTEST_INCLUDE_DIR})


add_executable(myTemplate ${SOURCES})

target_link_libraries(myTemplate doctest)

