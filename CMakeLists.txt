cmake_minimum_required(VERSION 3.30)

project(I_Chinese VERSION 0.1 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED CONFIG)
find_package(SQLite3 REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.c")

add_executable(I_Chinese ${SOURCES})

target_link_libraries(I_Chinese PRIVATE 
    SDL2::SDL2
    SQLite::SQLite3
)

target_include_directories(I_Chinese PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(I_Chinese PRIVATE include 
    ${SDL2_INCLUDE_DIRS}
    ${SQLite3_INCLUDE_DIRS}
)

target_compile_options(I_Chinese PRIVATE -Wall -Wextra -Wpedantic)


