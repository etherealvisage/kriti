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

bool Geometry::isAARectEmpty(Vector s, Vector e) {
    return e.x() <= s.x() || e.y() <= s.y();
}

void Geometry::intersectAARects(Vector &s, Vector &e, Vector s2, Vector e2) {
    s.setX(std::max(s.x(), s2.x()));
    s.setY(std::max(s.y(), s2.y()));
    e.setX(std::min(e.x(), e2.x()));
    e.setY(std::min(e.y(), e2.y()));
}

}  // namespace Math
}  // namespace Kriti
