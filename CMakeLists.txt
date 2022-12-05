cmake_minimum_required(VERSION 3.15)

project(Advent LANGUAGES CXX)

string(CONCAT WALL_OTHERS "$<"
    "$<AND:"
        "$<COMPILE_LANGUAGE:CXX>,"
        "$<NOT:"
            "$<CXX_COMPILER_ID:MSVC>"
        ">"
    ">:"
    "-Wall -Wextra"
">")

string(CONCAT WALL_MSVC "$<"
    "$<AND:"
        "$<COMPILE_LANGUAGE:CXX>,"
        "$<CXX_COMPILER_ID:MSVC>"
    ">:"
    "/W4"
">")

# enable folder hierarchy: filters on msvc
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# output to current binary directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# advent target
list(APPEND Advent_SOURCES
    # advent
    src/main.cpp

    # days
    src/days/common/common.h
    src/days/day01/day01.cpp
    src/days/day01/day01.h
    src/days/day02/day02.cpp
    src/days/day02/day02.h
    src/days/day03/day03.cpp
    src/days/day03/day03.h
    src/days/day04/day04.cpp
    src/days/day04/day04.h
    src/days/day05/day05.cpp
    src/days/day05/day05.h
)

list(APPEND Advent_INCLUDES
    # advent
    src/include

    # days
    src/days/common
    src/days/day01
    src/days/day02
    src/days/day03
    src/days/day04
    src/days/day05
)

list(APPEND Advent_VENDOR_SOURCES
)
list(APPEND Advent_VENDOR_INCLUDES
)

add_executable(Advent)
target_sources(Advent PRIVATE
    ${Advent_SOURCES}
)
target_include_directories(Advent PRIVATE
    ${Advent_INCLUDES}
)
target_include_directories(Advent SYSTEM PRIVATE
    ${Advent_VENDOR_INCLUDES}
)
target_link_libraries(Advent)
target_compile_features(Advent PRIVATE cxx_std_23)
target_compile_options(Advent PRIVATE
    ${WALL_OTHERS} ${WALL_MSVC}
)

# fmt
add_subdirectory(vendor/fmt-9.1.0)
target_link_libraries(Advent fmt::fmt)

# msvc-specific advent settings
if(MSVC)
    set_target_properties(Advent PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data
    )
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        PROPERTY VS_STARTUP_PROJECT Advent
    )
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${Advent_SOURCES})
endif()
