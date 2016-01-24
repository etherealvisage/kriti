set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/)

find_package(Boost REQUIRED COMPONENTS filesystem system)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2_image REQUIRED)
include_directories(${SDL2IMAGE_INCLUDE_DIR})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})

if(${kritiBox2D})
    find_package(Box2D)
    include(${BOX2D_USE_FILE})
endif(${kritiBox2D})

if(${kritiBullet})
    find_package(Bullet)
    include_directories(${BULLET_INCLUDE_DIRS})
endif(${kritiBullet})

set(kritiLibraries
    kriti
    ${Boost_LIBRARIES}
    ${BULLET_LIBRARIES}
    ${BOX2D_LIBRARIES}
    ${SDL2_LIBRARY}
    ${SDL2IMAGE_LIBRARY}
    ${OPENGL_LIBRARIES}
    ${FREETYPE_LIBRARY}
    # for clock_gettime().
    rt
)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../headers)
link_directories(${CMAKE_CURRENT_LIST_DIR}/..)
