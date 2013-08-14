add_definitions(-Wall -Wextra -std=c++11)
add_definitions(-Wno-unused-parameter)
add_definitions(-g)

aux_source_directory(. dotSources)
aux_source_directory(math mathSources)
aux_source_directory(interface interfaceSources)
aux_source_directory(event eventSources)
aux_source_directory(context contextSources)
aux_source_directory(game gameSources)
aux_source_directory(gui guiSources)
aux_source_directory(render renderSources)
aux_source_directory(physics physicsSources)
aux_source_directory(profile profileSources)
aux_source_directory(track trackSources)

include_directories(.)

set(sources
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
    ${trackSources}
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

include_directories(${pugixmlInclude})

add_executable(kriti ${sources})

target_link_libraries(kriti
    # pugixml from source tree
    pugixml

    ${Boost_LIBRARIES}
    ${BULLET_LIBRARIES}
    ${SDL2_LIBRARY}
    ${SDL2IMAGE_LIBRARY}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARY}
    # for clock_gettime().
    rt
)
