#include "Geometry.h"

namespace Kriti {
namespace Math {

Vector Geometry::closestPoint(Vector l1, Vector l2, Vector p) {
#if 0
    Vector d = l2-l1;

    return (p-l1).projectOnto(d) + l1;
#else
    Vector d = l2-l1;

    double t = d.dot(p-l1);

    t /= d.dot(d);

    return l1 + t*d;
#endif
}

Vector Geometry::closestSegmentPoint(Vector l1, Vector l2, Vector p) {
    Vector d = l2-l1;

    double t = d.dot(p-l1);

    t /= d.dot(d);

    if(t < 0) t = 0;
    else if(t > 1) t = 1;

    return l1 + t*d;
}

}  // namespace Math
}  // namespace Kriti
