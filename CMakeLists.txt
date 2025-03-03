cmake_minimum_required(VERSION 3.10)
project(Server_App C)

# Set directories
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(BUILD_DIR ${CMAKE_BINARY_DIR})

# Add include directory
include_directories(${INCLUDE_DIR})

# Create list of source files
set(SOURCES
    ${SRC_DIR}/Server_Application.c
    ${SRC_DIR}/Functions.c
)

# Create executable
add_executable(App ${SOURCES})

# Set output directory
set_target_properties(App PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}
)

# Optional: Add compiler flags if needed
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

message(STATUS "CMake build configuration completed")