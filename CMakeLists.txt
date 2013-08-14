cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/)

project(kriti C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

add_definitions(-DKRITI_DATA_PATH="data/")
add_definitions(-DKRITI_CONFIG_PATH="kriti.xml")

add_subdirectory(libs)
add_subdirectory(src)
