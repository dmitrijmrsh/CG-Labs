cmake_minimum_required(VERSION 3.10)

project(lab_02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_policy(SET CMP0072 NEW)

find_package(SFML 2.5 COMPONENTS window graphics system REQUIRED)
find_package(OpenGL REQUIRED)

set(SOURCES src/main.cpp src/impl/Vector3f_impl.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} sfml-window sfml-graphics sfml-system OpenGL::GL GLU)