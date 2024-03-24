cmake_minimum_required(VERSION 3.0)
project(Eu_Carrinho)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLUT_INCLUDE_DIR})

add_executable(Eu_Carrinho ${SOURCE_FILES})

target_link_libraries(Eu_Carrinho ${OPENGL_LIBRARIES})
target_link_libraries(Eu_Carrinho ${GLUT_LIBRARIES})