###################################################################################################
# Some settings

cmake_minimum_required(VERSION 3.0)
project(Bounce)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-O2 -Wall -Wextra -pedantic -Werror -Wno-unused-parameter)
endif()

include_directories(RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} include)

# powered by git_watcher.cmake; from https://github.com/andrew-hardin/cmake-git-version-tracking

# Define the two required variables before including
# the source code for watching a git repository.
set(PRE_CONFIGURE_FILE "src/bounce/version/version.cpp.in")
set(POST_CONFIGURE_FILE "src/bounce/version/version.cpp")
include(git_watcher.cmake)

# Create a library out of the compiled post-configure file.
add_library(git STATIC ${POST_CONFIGURE_FILE})
target_include_directories(git PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_dependencies(git check_git)

###################################################################################################
## LIBRARY

set(LIB bounce)

file(GLOB_RECURSE LIBRARY_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/bounce/*.cpp")

add_library(${LIB} STATIC ${LIBRARY_SOURCES})
target_compile_definitions(${LIB} PRIVATE RESOURCES_DIR="${RESOURCES_DIR}")
set_property(TARGET ${LIB} PROPERTY CXX_STANDARD 20)
target_link_libraries(${LIB} git)

###################################################################################################
## EXTERNAL LIBRARIES

find_package(Armadillo REQUIRED)
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${ARMADILLO_INCLUDE_DIRS})
list(APPEND EXT_LIB ${ARMADILLO_LIBRARIES})

find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})
list(APPEND EXT_LIB ${FREETYPE_LIBRARIES})
set(GLFW_LIB glfw)

find_package(nlohmann_json REQUIRED)
list(APPEND EXT_LIB ${nlohmann_json_LIBRARIES})

if (${CMAKE_SYSTEM_NAME} STREQUAL Darwin)
    message("System is MacOS.")
    find_package(GLFW3 REQUIRED)
    include_directories(${GLFW3_INCLUDE_DIRS})
    set(RESOURCES_DIR "/opt/local/${EXE}/resources")
    find_package(portaudio REQUIRED)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL Linux)
    message("System is Linux.")
    set(EXTRA_LIBS X11)
    set(RESOURCES_DIR "/opt/${EXE}/resources")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL WINDOWS)
    message("System is Windows.")
    set(GLFW_LIB glfw3)
    set(RESOURCES_DIR "%APPDATA%\\${EXE}\\resources")
else()
    message("UNKNOWN SYSTEM!")
endif()

list(APPEND EXT_LIB ${GLFW_LIB} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${EXTRA_LIBS})
include_directories(${OPENGL_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} ${GLEW_INCLUDE_DIR})

include_directories(/usr/local/include)
list(APPEND EXT_LIB portaudio)

###################################################################################################
## DEMO

set(EXE bounce-demo)
file(GLOB_RECURSE DEMO_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/demo/*.cpp")
add_executable(${EXE} ${DEMO_SOURCES})
set_property(TARGET ${EXE} PROPERTY CXX_STANDARD 20)

target_link_libraries(${EXE} ${LIB} ${EXT_LIB})

###################################################################################################
## DOCUMENTATION

add_subdirectory ("docs")

###################################################################################################
## TESTS

enable_testing()
find_package(GTest REQUIRED)
set(TEST_EXE bounce-tests)
include(GoogleTest)
file(GLOB_RECURSE TEST_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/tests/*.cpp")
add_executable(${TEST_EXE} ${TEST_SOURCES})
set_property(TARGET ${TEST_EXE} PROPERTY CXX_STANDARD 20)
target_link_libraries(${TEST_EXE} ${LIB} ${EXT_LIB} ${GTEST_LIBRARIES})
gtest_discover_tests(${TEST_EXE})
