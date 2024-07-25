#!/bin/bash

# Set the directories
INCLUDE_DIR=./Headers
SRC_DIR=./Source
BUILD_DIR=./Build

# Set the output executable name
OUTPUT=$BUILD_DIR/App

# Create the build directory if it doesn't exist
mkdir -p $BUILD_DIR

# Compile the source files
gcc -I$INCLUDE_DIR -c $SRC_DIR/Server_Application.c -o $BUILD_DIR/Server_Application.o
gcc -I$INCLUDE_DIR -c $SRC_DIR/Functions.c -o $BUILD_DIR/Functions.o

# Link the object files into an executable
gcc $BUILD_DIR/Server_Application.o $BUILD_DIR/Functions.o -o $OUTPUT

# Print a success message
echo "Build successful. Executable created: $OUTPUT"
