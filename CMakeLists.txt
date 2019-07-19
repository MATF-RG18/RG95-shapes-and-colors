cmake_minimum_required(VERSION 3.12)
project(RG95-shapes-and-colors CXX)

set(CMAKE_CXX_STANDARD 14)

link_libraries(GL)
link_libraries(GLU)
link_libraries(glut)

add_executable(RG95-shapes-and-colors src/main.cpp src/shapes.cpp src/shapes.hpp src/mainCube.hpp src/mainCube.cpp)