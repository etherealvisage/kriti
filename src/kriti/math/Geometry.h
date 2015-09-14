#ifndef KRITI_MATH__GEOMETRY_H
#define KRITI_MATH__GEOMETRY_H

#include "Vector.h"

namespace Kriti {
namespace Math {

class Geometry {
public:
    static Vector closestPoint(Vector l1, Vector l2, Vector p);
    static Vector closestSegmentPoint(Vector l1, Vector l2, Vector p);
};

}  // namespace Math
}  // namespace Kriti

#endif
