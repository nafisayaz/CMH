
mkdir -p libs/pugixml
pushd pugixml
mkdir -p build  

cmake . build -DBUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../3plibs/pugixml
cmake --build . --config Release
cmake --build . --target install 

cmake . build -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../3plibs/pugixml
cmake --build . --config Release
cmake --build . --target install
popd 

