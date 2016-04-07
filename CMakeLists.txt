# Clion comes with cmake 3.3. However, Linux Mint 17.3 has version 2.8.
cmake_minimum_required(VERSION 2.8)
project(FlashDriver)

# Uncomment to enable 'debug' code
#add_definitions(-DDEBUG)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wsign-conversion -Werror -Wall -Wextra -Wno-unused-parameter -pedantic -g -O0 -ansi -std=c++11")

# Project directory structure. DO NOT CHANGE.
set(APP_DIR "app") # Where the application main() code resides
set(SOURCE_DIR "src") # Where the source resides
set(TEST_DIR "tests") # Where the tests for the source reside
set(INC_DIR "include") # The headers for the source code
set(DOC_DIR "doc") # The project's documentation
set(MOCK_INC_DIR "mock/inc") # Where the header of the mocks reside
set(MOCK_SRC_DIR "mock/src") # Where the source of the mocks reside

# Project target names. Change as required.
set(PROJ_LIB "projlib")
set(TEST_RUNNER "testrunner")
set(APPLICATION "application")

include_directories(${INC_DIR})
include_directories(${MOCK_INC_DIR})
include_directories("/usr/include/gtest") # Google Test headers
include_directories("/usr/include/gmock") # Google Mock headers

# Create the directories if they do not already exist
file(MAKE_DIRECTORY ${APP_DIR})
file(MAKE_DIRECTORY ${SOURCE_DIR})
file(MAKE_DIRECTORY ${TEST_DIR})
file(MAKE_DIRECTORY ${INC_DIR})
file(MAKE_DIRECTORY ${DOC_DIR})
file(MAKE_DIRECTORY ${MOCK_INC_DIR})
file(MAKE_DIRECTORY ${MOCK_SRC_DIR})

# Get the file names from each directory
file(GLOB APP_FILES "${APP_DIR}/*.cpp")
file(GLOB SOURCE_FILES "${SOURCE_DIR}/*.cpp")
file(GLOB TEST_FILES "${TEST_DIR}/*.cpp")
file(GLOB MOCK_SRC_FILES "${MOCK_SRC_DIR}/*.cpp")
file(GLOB INC_FILES "${INC_DIR}/*.h*")
file(GLOB MOCK_INC_FILES "${MOCK_INC_DIR}/*.h*")

# Create a library from the source code.
# Note: INC_FILES have to be included so the auto completion
# and code generation work. This has to be done for all targets.
add_library(${PROJ_LIB} STATIC ${SOURCE_FILES} ${INC_FILES})

# Create the application's executable, using the source library.
#add_executable(${APPLICATION} ${APP_FILES} ${INC_FILES})
#target_link_libraries(${APPLICATION} ${PROJ_LIB})

# Create the Google Test Runner, with Google Test's libraries
# and this project's source library
add_executable(${TEST_RUNNER} ${TEST_FILES} ${MOCK_SRC_FILES} ${INC_FILES} ${MOCK_INC_FILES})
target_link_libraries(${TEST_RUNNER} "gtest")
target_link_libraries(${TEST_RUNNER} "gmock")
target_link_libraries(${TEST_RUNNER} "gtest_main")
target_link_libraries(${TEST_RUNNER} "pthread")
target_link_libraries(${TEST_RUNNER} ${PROJ_LIB})

