#!bin/bash

BUILD_DIR=build

mkdir -p $BUILD_DIR
cd $BUILD_DIR

cmake ..
cmake --build .

cd ..
echo "Built project in /build"
