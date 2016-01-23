Math library
============

The math library falls into two categories: vector math and computational
geometry. All of the following functionality is present inside the
``Kriti::Math`` namespace, and as such this will be dropped from the
descriptions for brevity.

Vector math
-----------

TODO: fill out

There are several useful classes in the vector math library. The first, and
most-oft-used, is ``Vector``. This represents a three-dimensional vector, and
has overloaded operators for most common operations. Other member functions
that may be of interest are ``length()``, ``length2()``, ``cross()``,
``dot()``, ``projectOnto()``, and the ``toString()`` function. Individual
components are accessible by ``vector.x()`` etc. as well as ``vector[1]``.

There is also a ``Point`` class, which inherits from ``Vector``. This is
intended for use in places where you distinctly have a location in 3D space as
opposed to a difference between locations. Due to the inheritance, a ``Point``
can be used anywhere a ``Vector`` can, but not vice-versa.

The ``Matrix`` class represents a standard 4x4 matrix, stored in column-major
ordering internally. Components are accessible by ``matrix(0, 3)``, which
accesses the last element in the first column. Note that the ``Matrix`` class
has overloaded operators, and in particular the ``Matrix * Point`` operator
behaves differently than the ``Matrix * Vector`` operator.

Finally, the ``Quaternion`` class is present, providing a full library for
the use of unit quaternions for representing rotations. Useful functionality
is present in the overloaded operators, the ``toMatrix()`` function, and the
``slerp()`` function.

TODO: add view calculation etc.

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
