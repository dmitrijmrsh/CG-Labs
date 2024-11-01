cmake_minimum_required(VERSION 3.10)

project(02-rendering)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)

add_executable(lab_01 src/main.cpp src/impl/Point_impl.cpp src/impl/SDL_functions_impl.cpp)

target_link_libraries(lab_01 ${SDL2_LIBRARIES})

include_directories(${SDL2_INCLUDE_DIRS})