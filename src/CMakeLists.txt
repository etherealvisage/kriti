add_definitions(-Wall -Wextra -std=c++11)
add_definitions(-Wno-unused-parameter -Wno-sign-compare)
add_definitions(-g)

aux_source_directory(assimp assimpSources)
aux_source_directory(pugixml pugixmlSources)

aux_source_directory(kriti dotSources)
aux_source_directory(kriti/math mathSources)
aux_source_directory(kriti/interface interfaceSources)
aux_source_directory(kriti/event eventSources)
aux_source_directory(kriti/context contextSources)
aux_source_directory(kriti/game gameSources)
aux_source_directory(kriti/gui guiSources)
aux_source_directory(kriti/render renderSources)
aux_source_directory(kriti/physics physicsSources)
aux_source_directory(kriti/profile profileSources)
aux_source_directory(kriti/scene sceneSources)
aux_source_directory(kriti/state stateSources)

include_directories(.)

set(sources
    ${assimpSources}
    ${pugixmlSources}

    ${dotSources}
    ${mathSources}
    ${interfaceSources}
    ${eventSources}
    ${contextSources}
    ${gameSources}
    ${guiSources}
    ${renderSources}
    ${physicsSources}
    ${profileSources}
    ${sceneSources}
    ${stateSources}
)

find_package(Boost COMPONENTS filesystem system signals)
include_directories(${Boost_INCLUDE_DIR})

find_package(Bullet)
include_directories(${BULLET_INCLUDE_DIRS})

find_package(SDL2)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2_image)
include_directories(${SDL2IMAGE_INCLUDE_DIR})

find_package(OpenGL)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(GLEW)
include_directories(${GLEW_INCLUDE_DIR})

add_library(kriti ${sources})

set(kritiLibraries CACHE INTERNAL
    ${Boost_LIBRARIES}
    ${BULLET_LIBRARIES}
    ${SDL2_LIBRARY}
    ${SDL2IMAGE_LIBRARY}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARY}
    # for clock_gettime().
    rt
)
