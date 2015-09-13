add_subdirectory(pugixml)
set(ASSIMP_BUILD_TESTS CACHE INTERNAL OFF)
set(ASSIMP_BUILD_STATIC_LIB CACHE INTERNAL ON)
set(ASSIMP_BUILD_ASSIMP_TOOLS CACHE INTERNAL OFF)
set(assimpInclude ${CMAKE_CURRENT_LIST_DIR}/assimp/include
    CACHE INTERNAL "assimp include directory")
add_subdirectory(assimp)
