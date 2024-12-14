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

set(ASSET_DIR "${CMAKE_SOURCE_DIR}/assets")

# Copy assets to the build directory
file(GLOB ASSETS_FILES "${ASSET_DIR}/*")

# Copy the assets into the output folder (where the executable is built)
foreach(ASSET ${ASSETS_FILES})
    get_filename_component(ASSET_NAME ${ASSET} NAME)
    add_custom_command(TARGET I_Chinese POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${ASSET} $<TARGET_FILE_DIR:I_Chinese>/assets/${ASSET_NAME}
    )
endforeach()

