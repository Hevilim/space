cmake_minimum_required(VERSION 4.0)
project(space)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} src/main.cpp)

find_package(SDL3 REQUIRED CONFIG)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

configure_file(${CMAKE_SOURCE_DIR}/sample.bmp ${CMAKE_BINARY_DIR}/sample.bmp COPYONLY)
