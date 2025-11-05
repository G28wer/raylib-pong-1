#!/bin/bash
set -e

BUILD_TYPE=${1:-Debug}

BUILD_TYPE=$(echo "$BUILD_TYPE" | awk '{print toupper(substr($0,1,1)) tolower(substr($0,2))}')

echo "Building in $BUILD_TYPE mode..."

mkdir -p build
cd build

cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..
make -j$(nproc)

EXEC="./bin/$BUILD_TYPE/raylib_project"

if [ -f "$EXEC" ]; then
    echo "Running $EXEC"
    $EXEC
else
    echo "Executable not found: $EXEC"
fi
