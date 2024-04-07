cmake_minimum_required(VERSION 3.26)
project(RayTracingSDL C)

set(SDL2_PATH "/home/marker/KindaGraphicsSDL/SDL")
find_package(SDL2 REQUIRED)
set(CMAKE_C_STANDARD 11)
include_directories( ${SDL2_INCLUDE_DIR} )
add_executable(RayTracingSDL main.c
        Constants.h
        Vector.c
        Vector.h
        Other.c
        Other.h
        Objects.c
        Objects.h
        list.c
        list.h
        Camera.c
        Camera.h)
target_link_libraries(RayTracingSDL ${SDL2_LIBRARY} )