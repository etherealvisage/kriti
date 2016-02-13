add_definitions(-Wall -Wextra)
add_definitions(-Wno-unused-parameter -Wno-sign-compare)
add_definitions(-g)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

aux_source_directory(assimp assimpSources)
aux_source_directory(pugixml pugixmlSources)

aux_source_directory(kriti dotSources)
if(${kritiBullet})
    aux_source_directory(kriti/bullet bulletSources)
endif(${kritiBullet})
if(${kritiBox2D})
    aux_source_directory(kriti/box2d box2dSources)
endif(${kritiBox2D})
aux_source_directory(kriti/data dataSources)
aux_source_directory(kriti/gui guiSources)
aux_source_directory(kriti/interface interfaceSources)
aux_source_directory(kriti/math mathSources)
aux_source_directory(kriti/profile profileSources)
aux_source_directory(kriti/render renderSources)
aux_source_directory(kriti/scene sceneSources)
aux_source_directory(kriti/state stateSources)

include_directories(.)

set(sources
    ${assimpSources}
    ${pugixmlSources}

    ${dotSources}
    ${box2dSources}
    ${bulletSources}
    ${dataSources}
    ${eventSources}
    ${guiSources}
    ${interfaceSources}
    ${mathSources}
    ${profileSources}
    ${renderSources}
    ${sceneSources}
    ${stateSources}
)

add_library(kriti ${sources})
