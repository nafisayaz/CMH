cmake_minimum_required(VERSION 3.5...3.30)

project(PocJsonTest VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)  # Ensure C++17 or later
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS ON)
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME}
    cmhTest.cpp
    # config.cpp
    # ParserTest.cpp
    # MainTest.cpp
    # ParserImpl.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../core/third-party/3plibs/nlohmann/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../core/third-party/3plibs/toml++/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../core/third-party/3plibs/pugixml/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../core/include
)

target_link_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../build/
)

set(CMAKE_PREFIX_PATH ../../build/usr/gbs ${CMAKE_PREFIX_PATH})
# find_package(cmh REQUIRED)
find_package(GTest REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    GTest::GTest 
    GTest::Main
    cmh
    stdc++fs
)

target_compile_definitions( ${PROJECT_NAME} PUBLIC
    CMH_DLL       # You’re using a DLL/shared object
    CMH_JSON      # Enable feature
    CMH_TOML
)


# # --- Install Rules ---
# # Install headers
# install(DIRECTORY include/ DESTINATION include)

# # Install library
# install(TARGETS ${PROJECT_NAME}
#     LIBRARY DESTINATION lib
#     ARCHIVE DESTINATION lib
#     RUNTIME DESTINATION bin  # For Windows .dll
# )

