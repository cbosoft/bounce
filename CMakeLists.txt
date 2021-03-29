cmake_minimum_required(VERSION 3.0)

project(Bounce VERSION "0.1.0")
set(EXE bounce)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")
add_executable(${EXE} ${SOURCES})

set_property(TARGET ${EXE} PROPERTY CXX_STANDARD 11)

find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})
target_link_libraries(${EXE} ${ARMADILLO_LIBRARIES})

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${EXE} ${SDL2_LIBRARIES})

if(MSVC)
    target_compile_options(${EXE} PRIVATE /W4 /WX)
else()
    target_compile_options(${EXE} PRIVATE -Wall -Wextra -pedantic -Werror -Wno-unused-parameter)
endif()