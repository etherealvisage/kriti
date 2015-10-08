### Kriti game engine

Kriti is a game engine for games written in C++11. It needs:

- CMake
- clang/gcc with c++11 support
- boost (tested with 1.58)
- SDL 2.0
- SDL_image 2.0
- OpenGL 3.1
- GLEW
- bullet physics engine
- Freetype 

To install these requirements on Debian, run:

    apt-get install \
        cmake g++ libboost-dev libboost-filesystem-dev libboost-system-dev \
        libsdl2-dev libsdl2-image-dev libglew-dev libbullet-dev \
        libfreetype6-dev

### Features

Some existing features of kriti include:

- Full multi-stage rendering pipeline with RTT and blending
- Functional GUI library
- Open Asset Import Library integration to load almost all 3D models
- Integration with bullet physics engine, either with render geometry or with
  simplified physics model
- XML-based configuration available (but not required) for many engine objects

Planned features:

- Conditional geometry (à la LoD rendering)
- Sound integration

### Compiling

To compile, run `make redep` and then `make`. This will generate the
`libkriti.a` static library. You can then optionally create a distribution
version of kriti by running the `make_dist_version.sh` shell script.

### Documentation

Forthcoming!

### Authors

Contact: ethereal@ethv.net
