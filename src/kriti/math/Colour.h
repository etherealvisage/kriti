#ifndef KRITI_MATH__COLOUR_H
#define KRITI_MATH__COLOUR_H

#include <string>
#include <cmath>

namespace Kriti {
namespace Math {

class Colour {
private:
    double m_r, m_g, m_b, m_a;
public:
    Colour() : m_r(0), m_g(0), m_b(0), m_a(1) {}
    Colour(double r, double g, double b, double a = 1.0)
        : m_r(r), m_g(g), m_b(b), m_a(a) {}
    Colour(std::string description);

    double r() const { return m_r; }
    double g() const { return m_g; }
    double b() const { return m_b; }
    double a() const { return m_a; }

    void setR(double r) { m_r = r; }
    void setG(double g) { m_g = g; }
    void setB(double b) { m_b = b; }
    void setA(double a) { m_a = a; }

    double &operator[](int which) {
        switch(which) {
        case 0:
            return m_r;
        case 1:
            return m_g;
        case 2:
            return m_b;
        case 3:
            return m_a;
        default:
            return m_r;
        }
    }

    double length() const {
        return std::sqrt(m_r*m_r + m_g*m_g + m_b*m_b + m_a*m_a);
    }

    double length2() const {
        return m_r*m_r + m_g*m_g + m_b*m_b + m_a*m_a;
    }

    Colour operator+(const Colour &other) const {
        return Colour(m_r + other.m_r, m_g + other.m_g, m_b + other.m_b,
            m_a + other.m_a);
    }

    Colour &operator+=(const Colour &other) {
        m_r += other.m_r;
        m_g += other.m_g;
        m_b += other.m_b;
        m_a += other.m_a;
        return *this;
    }

    Colour operator-(const Colour &other) const {
        return Colour(m_r - other.m_r, m_g - other.m_g, m_b - other.m_b,
            m_a - other.m_a);
    }

    Colour &operator-=(const Colour &other) {
        m_r -= other.m_r;
        m_g -= other.m_g;
        m_b -= other.m_b;
        m_a -= other.m_a;
        return *this;
    }

    Colour operator*(const Colour &other) const {
        return Colour(m_r * other.m_r, m_g * other.m_g, m_b * other.m_b,
            m_a * other.m_a);
    }

    Colour operator*(double scalar) const {
        return Colour(m_r * scalar, m_g * scalar, m_b * scalar, m_a * scalar);
    }

    void operator*=(double scalar) {
        m_r *= scalar;
        m_g *= scalar;
        m_b *= scalar;
        m_a *= scalar;
    }

    Colour operator/(double scalar) const {
        return Colour(m_r / scalar, m_g / scalar, m_b / scalar, m_a / scalar);
    }

    void operator/=(double scalar) {
        m_r /= scalar;
        m_g /= scalar;
        m_b /= scalar;
        m_a /= scalar;
    }

    Colour operator-() const {
        return Colour(-m_r, -m_g, -m_b, -m_a);
    }

    double dot(const Colour &other) const {
        return m_r*other.m_r + m_g*other.m_g + m_b*other.m_b + m_a*other.m_a;
    }

    bool operator==(const Colour &other) const {
        return m_r == other.m_r && m_g == other.m_g && m_b == other.m_b
            && m_a == other.m_a;
    }

    bool operator!=(const Colour &other) const {
        return !(*this == other);
    }

    std::string toString() const;
};

// make Americans happy
using Color = Colour;

}  // namespace Math
}  // namespace Kriti

#endif
