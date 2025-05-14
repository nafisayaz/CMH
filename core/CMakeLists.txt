cmake_minimum_required(VERSION 3.5...3.30)

project(cmh VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)  # Ensure C++17 or later
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS ON)
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(BUILD_SHARED_LIBS ON)

add_library(${PROJECT_NAME}
    ./src/jsonParser.cpp
    ./src/tomlParser.cpp
    ./src/systemConfig.cpp
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third-party/3plibs/pugixml/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third-party/3plibs/toml++/include
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third-party/3plibs/pugixml/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third-party/3plibs/toml++/include
)

# target_include_directories(${PROJECT_NAME}
#     PUBLIC
#         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/third-party/3plibs/pugixml/include>
#         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/third-party/3plibs/toml++/include>
#         $<INSTALL_INTERFACE:include>
# )

target_link_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/third-party/3plibs/pugixml/lib
)

# target_link_directories(${PROJECT_NAME}
#     PUBLIC
#         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/third-party/3plibs/pugixml/lib>
# )


target_link_libraries(${PROJECT_NAME} PUBLIC
    pugixml
)

target_compile_definitions( ${PROJECT_NAME} PUBLIC
    CMH_DLL       # Assume you're building or using a shared lib
    CMH_EXPORT    # Only defined when building the cmh library itself
    CMH_JSON
    CMH_TOML
)

# # --- Install Rules ---
# # Install headers
# install(DIRECTORY include/ DESTINATION include)

# # Install library
# install(TARGETS ${PROJECT_NAME}
#     EXPORT cmhTargets 
#     LIBRARY DESTINATION lib
#     ARCHIVE DESTINATION lib
#     RUNTIME DESTINATION bin  # For Windows .dll
# )


# # Optionally export CMake config
# install(EXPORT cmhTargets
#     FILE cmhTargets.cmake
#     FILE cmhConfig.cmake
#     NAMESPACE cmh::
#     DESTINATION lib/cmake/cmh
# )
