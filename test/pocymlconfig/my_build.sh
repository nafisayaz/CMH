#!/usr/bin/bash

rm -rf build

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release 

cmake --build build --config Release

pushd build/
./pocymlconfig
popd

