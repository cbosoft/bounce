cmake_minimum_required(VERSION 3.0)

project(Bounce VERSION "0.1.0")
set(EXE bounce)

file(GLOB_RECURSE COMMON_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/common/*.cpp")

add_executable(${EXE} src/demo_main/main.cpp ${COMMON_SOURCES})

set_property(TARGET ${EXE} PROPERTY CXX_STANDARD 11)

find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})
target_link_libraries(${EXE} ${ARMADILLO_LIBRARIES})

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
if(${SDL_LIBRARIES})
  target_link_libraries(${EXE} ${SDL_LIBRARIES})
else()
  # arch has a strange way of storing the SDL find results
  target_link_libraries(${EXE} SDL2::SDL2)
endif()

if(MSVC)
    target_compile_options(${EXE} PRIVATE /W4 /WX)
else()
    target_compile_options(${EXE} PRIVATE -Wall -Wextra -pedantic -Werror -Wno-unused-parameter)
endif()

enable_testing()

find_package(GTest REQUIRED)
include(GoogleTest)
file(GLOB_RECURSE TEST_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "tests/*.cpp")
add_executable(bounce_tests ${TEST_SOURCES} ${COMMON_SOURCES})
set_property(TARGET bounce_tests PROPERTY CXX_STANDARD 11)
target_link_libraries(bounce_tests ${GTEST_LIBRARIES})
target_link_libraries(bounce_tests ${ARMADILLO_LIBRARIES})
if(${SDL_LIBRARIES})
  target_link_libraries(bounce_tests ${SDL_LIBRARIES})
else()
  target_link_libraries(bounce_tests SDL2::SDL2)
endif()
gtest_discover_tests(bounce_tests)
