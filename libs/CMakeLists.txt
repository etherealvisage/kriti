add_subdirectory(pugixml)
set(ASSIMP_BUILD_TESTS false)
set(ASSIMP_BUILD_STATIC_LIB true)
set(ASSIMP_BUILD_ASSIMP_TOOLS false)
set(assimpInclude ${CMAKE_CURRENT_LIST_DIR}/assimp/include
    CACHE INTERNAL "assimp include directory")
add_subdirectory(assimp)
