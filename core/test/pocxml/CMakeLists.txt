cmake_minimum_required(VERSION 3.5...3.30)

project(test VERSION 1.0.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../third-party/libs/pugixml/include
)

target_link_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../third-party/libs/pugixml/lib
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    pugixml
)

