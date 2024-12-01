cmake_minimum_required(VERSION 3.10)

project(Lab_03)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES 
    src/main.cpp
    src/impl/camera.cpp
    src/impl/cube.cpp
)

find_package(SFML 2.5 COMPONENTS window graphics system REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} sfml-window sfml-graphics sfml-system OpenGL::GL GLU)