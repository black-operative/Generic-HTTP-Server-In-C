cmake_minimum_required(VERSION 3.10)

# Set GCC before project is declared
set(CMAKE_C_COMPILER gcc)

project(App LANGUAGES C)

# Ensure C standard compatibility (optional)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Enable compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Set directories
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(BUILD_DIR "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_DIR}")

# Add include directory
include_directories("${INCLUDE_DIR}")

# Create list of source files
set(SOURCES
    "${SRC_DIR}/Server_Application.c"
    "${SRC_DIR}/Functions.c"
)

# Create executable
add_executable(App ${SOURCES})

# Add compiler warnings
target_compile_options(App PRIVATE
    -Wall
    -Wextra
    -pedantic
)

# Print configuration info
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Source Directory: ${SRC_DIR}")
message(STATUS "Include Directory: ${INCLUDE_DIR}")
message(STATUS "Build Directory: ${BUILD_DIR}")
message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compile Commands: ${CMAKE_BINARY_DIR}/compile_commands.json")
