cmake_minimum_required(VERSION 3.5...3.30)

project(pocjson VERSION 1.0.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME}
    cmhTest.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../third-party/3plibs/nlohmann/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
)

target_link_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../build/
)

find_package(GTest REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    GTest::GTest 
    GTest::Main
    cmh
    stdc++fs
)


target_compile_definitions( ${PROJECT_NAME} PUBLIC
    # CMH_XML
    CMH_JSON
    CMH_DLL
)
