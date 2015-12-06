add_definitions(-Wall -Wextra -std=c++11)
add_definitions(-Wno-unused-parameter -Wno-sign-compare)
add_definitions(-g)

aux_source_directory(assimp assimpSources)
aux_source_directory(pugixml pugixmlSources)

aux_source_directory(kriti dotSources)
aux_source_directory(kriti/data dataSources)
aux_source_directory(kriti/game gameSources)
aux_source_directory(kriti/gui guiSources)
aux_source_directory(kriti/interface interfaceSources)
aux_source_directory(kriti/math mathSources)
aux_source_directory(kriti/physics physicsSources)
aux_source_directory(kriti/profile profileSources)
aux_source_directory(kriti/render renderSources)
aux_source_directory(kriti/scene sceneSources)
aux_source_directory(kriti/state stateSources)

include_directories(.)

set(sources
    ${assimpSources}
    ${pugixmlSources}

    ${dotSources}
    ${dataSources}
    ${eventSources}
    ${gameSources}
    ${guiSources}
    ${interfaceSources}
    ${mathSources}
    ${physicsSources}
    ${profileSources}
    ${renderSources}
    ${sceneSources}
    ${stateSources}
)

add_library(kriti ${sources})
