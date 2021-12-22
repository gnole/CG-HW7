cmake_minimum_required(VERSION 3.15)
project(CG6)
set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)
find_package(OpenGL)
include_directories(${SFML_INCLUDE_DIRECTORIES})

add_executable(CG7 main.cpp)
target_link_libraries(CG7 PRIVATE sfml-system sfml-window sfml-graphics OpenGL)
