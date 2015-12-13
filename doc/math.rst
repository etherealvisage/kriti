Math library
============

The math library falls into two categories: vector math and computational
geometry. All of the following functionality is present inside the
``Kriti::Math`` namespace, and as such this will be dropped from the
descriptions for brevity.

Vector math
-----------

TODO: fill out

Computational geometry
----------------------

The computational geometry library is currently not yet complete and includes
basic 2D geometry functionality, such as:

 * ``Geometry::closestPoint``: finds the closest point on a line to
   another point ``p``.
 * ``Geometry::closestSegmentPoint``: finds the closest point on a line
   segment to another point ``p``.
 * ``Geometry::intersectAARect``: calculates the intersection of two
   axis-aligned rectangles and returns another axis-aligned rectangle.

TODO: finish filling out
