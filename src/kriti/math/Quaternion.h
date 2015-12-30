#ifndef KRITI_MATH__QUATERNION_H
#define KRITI_MATH__QUATERNION_H

#include "Vector.h"
#include "Matrix.h"

namespace Kriti {
namespace Math {

/** Unit quaternion class, used for rotations. */
class Quaternion {
private:
    double m_s;
    Vector m_v;
private:
    Quaternion(double s, Vector v) : m_s(s), m_v(v) {}
public:
    Quaternion() : m_s(1.0), m_v() {}
    Quaternion(const Vector &axis, double angle);

    void toAxisAngle(Vector &axis, double &angle) const;

    Quaternion conjugate() const {
        return Quaternion(m_s, -m_v);
    }

    /** Quaternion multiplication. */
    Quaternion operator*(const Quaternion &other) const {
        return Quaternion(
            m_s*other.m_s - m_v.dot(other.m_v),
            m_s*other.m_v + other.m_s*m_v + m_v.cross(other.m_v)
        );
    }

    /** Quaternion-vector multiplication (rotation). */
    Vector operator*(const Vector &other) const {
        return ((*this) * Quaternion(0.0, other) * conjugate()).m_v;
    }

    Matrix toMatrix() const;

    double angleTo(const Quaternion &other) const;
    double cosAngleTo(const Quaternion &other) const;
    Quaternion slerp(const Quaternion &other, double by) const;
};

inline Vector operator*(const Vector &vec, const Quaternion &quat) {
    return quat * vec;
}

}  // namespace Math
}  // namespace Kriti

#endif
