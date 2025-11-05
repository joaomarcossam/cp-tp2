cmake_minimum_required(VERSION 3.10)
project(trab2_paralela)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

include_directories(/usr/include)
include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SOURCES "src/*.c")
add_executable(main ${SOURCES})

target_compile_options(main PRIVATE -pg)
target_link_options(main PRIVATE -pg)

if(PARALLEL)
    target_compile_definitions(main PRIVATE PARALLEL)
endif()

if(LOG_CODE_ENABLED)
    target_compile_definitions(main PRIVATE LOG_CODE_ENABLED)
endif()

if(PRINT_RESULT)
    target_compile_definitions(main PRIVATE PRINT_RESULT)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address,undefined)
    message(STATUS "Debug build: sanitizers enabled (-fsanitize=address,undefined)")
endif()

target_link_libraries(main m)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")