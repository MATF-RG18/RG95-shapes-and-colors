cmake_minimum_required(VERSION 3.10)
project(RG95-shapes-and-colors CXX)

set(CMAKE_CXX_STANDARD 14)

link_libraries(GL)
link_libraries(GLU)
link_libraries(glut)

FILE(COPY images/pozadina.bmp DESTINATION "${CMAKE_BINARY_DIR}/images")
FILE(COPY images/tekstura_kutije.bmp DESTINATION "${CMAKE_BINARY_DIR}/images")

add_executable(RG95-shapes-and-colors src/main.cpp shapes/shapes.cpp shapes/shapes.hpp src/mainCube.hpp src/mainCube.cpp src/firstScene.cpp src/firstScene.hpp src/texture.cpp src/texture.hpp shapes/sphere.cpp shapes/cube.cpp shapes/triangularPrism.cpp shapes/cylinder.cpp shapes/star.cpp shapes/flower.cpp shapes/heart.cpp)