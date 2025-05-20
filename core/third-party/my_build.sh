# ------------------------ PUGIXML ----------------------

# mkdir -p 3plibs/pugixml
# pushd pugixml
# mkdir -p build  

# cmake . build -DBUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../3plibs/pugixml
# cmake --build . --config Release
# cmake --build . --target install 

# cmake . build -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../3plibs/pugixml
# cmake --build . --config Release
# cmake --build . --target install

# popd 

# # ----------------- TOML++ -----------------------------
# mkdir -p 3plibs/toml++
# pushd tomlplusplus
# mkdir -p build

# cmake . build -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../3plibs/toml++
# cmake --build . --config Release
# cmake --build . --target install

# cmake . build -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../3plibs/toml++
# cmake --build . --config Release
# cmake --build . --target install

# popd


# # ----------------- RAPIDYAML -----------------------------
# mkdir -p 3plibs/rapidyaml
# pushd rapidyaml
# mkdir -p build

# cmake . build -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DCMAKE_INSTALL_PREFIX=../3plibs/rapidyaml
# cmake --build . --config Release
# cmake --build . --target install

# cmake . build -DBUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DCMAKE_INSTALL_PREFIX=../3plibs/rapidyaml
# cmake --build . --config Release
# cmake --build . --target install
# popd


# ----------------- RAPIDYAML -----------------------------
mkdir -p 3plibs/yaml-cpp
pushd yaml-cpp
mkdir -p build

cmake . build -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DCMAKE_INSTALL_PREFIX=../3plibs/yaml-cpp
cmake --build . --config Release
cmake --build . --target install

cmake . build -DBUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DCMAKE_INSTALL_PREFIX=../3plibs/yaml-cpp
cmake --build . --config Release
cmake --build . --target install
popd



