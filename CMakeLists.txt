cmake_minimum_required(VERSION 3.30)

project(I_Chinese VERSION 0.1 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

add_executable(I_Chinese)

target_link_libraries(I_Chinese PRIVATE SDL2::SDL2)

target_include_directories(I_Chinese PRIVATE include ${SDL2_INCLUDE_DIRS})

add_subdirectory(src)

