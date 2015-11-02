Rendering
=========

Rendering model
---------------

The rendering model is based around three core objects: ``Render::Pipeline``,
``Render::Stage``, and ``Render::Renderable``. The idea is that a
``Render::Pipeline`` describes an entire rendering process, including all the
multi-stage passes, all the RTT, all the conditional rendering, everything.
This is done by breaking up the rendering process into individual ``Stage``
components that can be evaluated individually, with optional inter-``Stage``
dependencies.

Each ``Stage`` renders zero or more ``Renderable`` instances, which can be
thought of as any sort of self-contained object that can be rendered to an
image.

TODO: finish

Renderable objects
------------------


