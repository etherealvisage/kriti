add_definitions(-Wall -Wextra -std=c++11)

aux_source_directory(. dotSources)
aux_source_directory(math mathSources)
aux_source_directory(config configSources)
aux_source_directory(interface interfaceSources)
aux_source_directory(event eventSources)
aux_source_directory(context contextSources)
aux_source_directory(game gameSources)
aux_source_directory(render renderSources)
aux_source_directory(physics physicsSources)

include_directories(.)

set(sources
    ${dotSources}
    ${mathSources}
    ${configSources}
    ${interfaceSources}
    ${eventSources}
    ${contextSources}
    ${gameSources}
    ${renderSources}
    ${physicsSources}
)

find_package(Boost COMPONENTS filesystem system signals)
include_directories(${Boost_INCLUDE_DIR})

find_package(Bullet)
include_directories(${BULLET_INCLUDE_DIRS})

find_package(SDL)
include_directories(${SDL_INCLUDE_DIR})

find_package(SDL_image)
include_directories(${SDLIMAGE_INCLUDE_DIR})

find_package(OpenGL)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(GLEW)
include_directories(${GLEW_INCLUDE_DIR})

add_executable(kriti ${sources})

target_link_libraries(kriti
    ${Boost_LIBRARIES}
    ${BULLET_LIBRARIES}
    ${SDL_LIBRARY}
    ${SDLIMAGE_LIBRARY}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARY}
    # for clock_gettime().
    rt
)
