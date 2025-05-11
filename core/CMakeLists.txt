cmake_minimum_required(VERSION 3.5...3.30)

project(cmh VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)  # Ensure C++17 or later
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(BUILD_SHARED_LIBS ON)


add_library(${PROJECT_NAME}
    ./src/parser.cpp
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third-party/3plibs/pugixml/include

)
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third-party/3plibs/pugixml/include
)

target_link_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/third-party/3plibs/pugixml/lib
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    pugixml
)

target_compile_definitions( ${PROJECT_NAME} PUBLIC
    # CMH_XML
    CMH_JSON
    CMH_DLL
)

