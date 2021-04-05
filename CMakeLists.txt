cmake_minimum_required(VERSION 3.0)

###################################################################################################
# VERSION

# powered by git_watcher.cmake; from https://github.com/andrew-hardin/cmake-git-version-tracking

# Define the two required variables before including
# the source code for watching a git repository.
set(PRE_CONFIGURE_FILE "src/version.cpp.in")
set(POST_CONFIGURE_FILE "src/version.cpp")
include(git_watcher.cmake)

# Create a library out of the compiled post-configure file.
add_library(git STATIC ${POST_CONFIGURE_FILE})
target_include_directories(git PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_dependencies(git check_git)

###################################################################################################
# MAIN EXE

project(Bounce)
set(EXE bounce)

file(GLOB_RECURSE COMMON_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/common/*.cpp")

add_executable(${EXE} src/demo_main/main.cpp ${COMMON_SOURCES})
target_link_libraries(bounce git)

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


###################################################################################################
## TESTS

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
