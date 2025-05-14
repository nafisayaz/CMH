#!/usr/bin/bash

rm -rf ../build

cmake -S . -B ../build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=../build/usr/gbs

cmake --build ../build --config Debug

# cmake --install ../build
