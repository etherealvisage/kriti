Kriti architecture
==================

Submodules
----------

Kriti can considered to be built out of several different submodules:

 * The state engine; this is responsible for managing the state of different
   parts of a game and the engine.
 * The math library; this provides general 3D mathematics data-types,
   functions, as well as some 2D computational geometry functionality.
 * The rendering engine; this is where the 3D magic happens and pretty pictures
   are generated.
 * The scene library; this is where models are created and animated, cameras
   set up, and lights tweaked. Basically, the scene graph.
 * The interface library; this provides code to glue together the interface the
   user sees with the rest of the codebase.
 * The GUI library; this provides for all your interactive needs.
 * The physics integration; this provides a wrapper for Bullet, allowing for a
   unified interface within kriti for rendering and physics.

Message and logging system
--------------------------

Kriti has a very complete logging system, intended to be used mostly for
debugging.

Resource system
---------------

Kriti also has an external resource management system, intended to be agnostic
to the method used to actually store information. While at the moment this is a
simple wrapper around the host filesystem, the intention is that it will also
allow for loading from ZIP archives as well.

Buildsystem
-----------

Unlike some other game libraries, Kriti does not require much out of the
buildsystem. While only CMake integration is currently tested, it should be
straightforward to integrate with anything make-alike.

.. highlight:: cmake

To add Kriti into a project using CMake, simply add the following line
somewhere in your buildscripts::

    include(path-to-kriti/cmake/kriti-env.cmake)

Once that has been added, simply change your ``target_link_libraries`` line to
include ``${kritiLibraries}``.

.. highlight:: c++

Kriti will take over the ``main()`` function, leaving you to implement a
``gameEntryPoint()`` function somewhere in your source tree. This will be
explained further in the `Basics <basics.html>`_ section later.

TODO: finish explanation of project architecture.
