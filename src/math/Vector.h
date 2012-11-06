#ifndef KRITI_MATH__VECTOR_H
#define KRITI_MATH__VECTOR_H

#include <cmath>

#include "Constants.h"

namespace Kriti {
namespace Math {

/** 3D vector class. */
class Vector {
private:
    double m_x, m_y, m_z;
public:
    Vector(double x = 0.0, double y = 0.0, double z = 0.0)
        : m_x(x), m_y(y), m_z(z) {}

    double x() const { return m_x; }
    double y() const { return m_y; }
    double z() const { return m_z; }

    double length() const {
        return std::sqrt(m_x*m_x + m_y*m_y + m_z*m_z);
    }

    double length2() const {
        return m_x*m_x + m_y*m_y + m_z*m_z;
    }

    Vector normalized() const {
        double len = length();
        if(len > Constants::Epsilon) return Vector(m_x/len, m_y/len, m_z/len);
        return Vector();
    }

    Vector operator+(const Vector &other) const {
        return Vector(m_x + other.m_x, m_y + other.m_y, m_z + other.m_z);
    }

    Vector operator-(const Vector &other) const {
        return Vector(m_x - other.m_x, m_y - other.m_y, m_z - other.m_z);
    }

    Vector operator*(const Vector &other) const {
        return Vector(m_x * other.m_x, m_y * other.m_y, m_z * other.m_z);
    }

    Vector operator*(double scalar) const {
        return Vector(m_x * scalar, m_y * scalar, m_z * scalar);
    }

    void operator*=(double scalar) {
        m_x *= scalar;
        m_y *= scalar;
        m_z *= scalar;
    }

    Vector operator/(double scalar) const {
        return Vector(m_x / scalar, m_y / scalar, m_z / scalar);
    }

    void operator/=(double scalar) {
        m_x /= scalar;
        m_y /= scalar;
        m_z /= scalar;
    }

    Vector operator-() const {
        return Vector(-m_x, -m_y, -m_z);
    }

    double dot(const Vector &other) const {
        return m_x*other.m_x + m_y*other.m_y + m_z*other.m_z;
    }

    Vector cross(const Vector &other) const {
        return Vector(
            m_y*other.m_z - m_z*other.m_y,
            -(m_x*other.m_z - m_z*other.m_x),
            m_x*other.m_y - m_y*other.m_x
        );
    }

    Vector rotX(double angle) const {
        double s = std::sin(angle);
        double c = std::cos(angle);
        return Vector(
            m_x,
            m_y*c + m_y*s,
            -m_z*s + m_z*c
        );
    }

    Vector rotY(double angle) const {
        double s = std::sin(angle);
        double c = std::cos(angle);
        return Vector(
            m_x*c - m_x*s,
            m_y,
            m_z*s + m_z*c
        );
    }

    Vector rotZ(double angle) const {
        double s = std::sin(angle);
        double c = std::cos(angle);
        return Vector(
            m_x*c + m_y*s,
            -m_x*s + m_y*c,
            m_z
        );
    }

    bool operator==(const Vector &other) const {
        return m_x == other.m_x && m_y == other.m_y && m_z == other.m_z;
    }
};

inline Vector operator*(double scalar, const Vector &vector) {
    return Vector(
        vector.x() * scalar,
        vector.y() * scalar,
        vector.z() * scalar
    );
}

inline Vector operator/(double scalar, const Vector &vector) {
    return Vector(
        scalar / vector.x(),
        scalar / vector.y(),
        scalar / vector.z()
    );
}

}  // namespace Math
}  // namespace Kriti

#endif
