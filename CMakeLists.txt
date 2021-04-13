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
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${ARMADILLO_INCLUDE_DIRS})
target_link_libraries(${EXE} ${ARMADILLO_LIBRARIES})

find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})
target_link_libraries(${EXE} ${FREETYPE_LIBRARIES})

if (${CMAKE_SYSTEM} STREQUAL LINUX)
  set(EXTRA_LIBS X11)
endif()

if (${CMAKE_SYSTEM_NAME} STREQUAL Darwin)
    message("DARWIN!")
    find_package(GLFW3 REQUIRED)
    include_directories(${GLFW3_INCLUDE_DIRS})
else()
    message("Not DARWIN!")
endif()

if (CMAKE_SYSTEM STREQUAL WINDOWS)
  set(GLFW_LIB glfw3)
else()
  set(GLFW_LIB glfw)
endif()

target_link_libraries(${EXE} ${GLFW_LIB} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${EXTRA_LIBS})
include_directories(${OPENGL_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} ${GLEW_INCLUDE_DIR})

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
gtest_discover_tests(bounce_tests)
