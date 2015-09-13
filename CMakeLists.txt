cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/)

project(kriti C CXX)

add_definitions(-DKRITI_DATA_PATH="data/")
add_definitions(-DKRITI_CONFIG_PATH="kriti.xml")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
add_subdirectory(libs)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
add_subdirectory(src)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_LIST_DIR}/libkriti.a
    COMMAND ar -M < ${CMAKE_CURRENT_LIST_DIR}/merge.mri
    DEPENDS ${CMAKE_CURRENT_LIST_DIR}/libkriti_only.a
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

add_custom_target(
    static ALL
    DEPENDS ${CMAKE_CURRENT_LIST_DIR}/libkriti.a)

add_dependencies(static kriti_only pugixml assimp)
