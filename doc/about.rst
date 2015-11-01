About
=====

What is kriti?
--------------

Kriti is a 3D game engine for games written in C++. It aims to provide a
medium-weight approach so that while it imposes some structure on the game
you're trying to write, it also stays out of your way when you want to do
things yourself.

Kriti is cross-platform, using OpenGL as a rendering method and has been
written with platform compatibility in mind. Right now, it lacks support for
mobile platforms, though support for such is planned.

Features of kriti
-----------------

Current features:

 * Full multi-stage rendering pipeline with RTT and blending
 * GUI library
 * Open Asset Import Library integration to load almost all 3D models
 * Integration with bullet physics engine, either with render geometry or with
   simplified physics model
 * XML-based configuration available for many engine objects, including
   rendering pipeline configuration

Planned features:

 * Anti-aliasing (MSAA)
 * Conditional rendering (à la level-of-detail rendering)
 * Sound via OpenAL

Dependencies of kriti
---------------------

Kriti needs:

 * A C++11-capable compiler (gcc and clang tested so far)
 * Boost (at least version 1.55)
 * CMake (version 2.6 or later)
 * SDL 2.0
 * SDL_image 2.0
 * OpenGL 3.1 (or later) development libraries
 * GLEW
 * bullet physics engine
 * FreeType

Licensing
---------

The main kriti codebase is released under a 3-clause BSD license. That
essentially means you can do whatever you want with it, provided you don't
claim it as your own. Kriti also contains parts of several other open-source
libraries, relased under various licenses; see the COPYING file for more
details.

Authors
-------

 * Kent "ethereal" Williams-King
