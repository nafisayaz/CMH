#!/usr/bin/bash

rm -rf build

cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug 

cmake --build build --config Debug

# pushd build/
# ./pocjson init
# ./pocjson create SampleProject
# popd


pushd build/
./PocJsonTest 
popd

