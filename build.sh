#!/bin/bash

INCLUDE_DIR=./Headers
SRC_DIR=./Source
BUILD_DIR=./Build

OUTPUT=$BUILD_DIR/App

gcc -I $INCLUDE_DIR -c $SRC_DIR/Server_Application.c -o $BUILD_DIR/Server_Application.o
gcc -I $INCLUDE_DIR -c $SRC_DIR/Functions.c -o $BUILD_DIR/Functions.o
gcc $BUILD_DIR/Server_Application.o $BUILD_DIR/Functions.o -o $OUTPUT

echo "Build successful!"