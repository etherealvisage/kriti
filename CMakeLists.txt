cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/)

project(kriti C CXX)

add_definitions(-DKRITI_DATA_PATH="data/")
add_definitions(-DKRITI_CONFIG_PATH="kriti.xml")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
add_subdirectory(libs)

add_subdirectory(src)
