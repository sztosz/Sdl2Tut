cmake_minimum_required(VERSION 3.3)
project(Sdl2Tut)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})

add_executable(Sdl2Tut01 src/01/01.cpp)
target_link_libraries(Sdl2Tut01 ${SDL2_LIBRARY})

add_executable(Sdl2Tut02 src/02/02.cpp)
target_link_libraries(Sdl2Tut02 ${SDL2_LIBRARY})

add_executable(Sdl2Tut03 src/03/03.cpp)
target_link_libraries(Sdl2Tut03 ${SDL2_LIBRARY})

add_executable(Sdl2Tut04 src/04/04.cpp)
target_link_libraries(Sdl2Tut04 ${SDL2_LIBRARY})
