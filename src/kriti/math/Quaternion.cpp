#include "Quaternion.h"

namespace Kriti {
namespace Math {

Quaternion::Quaternion(const Vector &axis, double angle) {
    m_s = std::cos(angle/2.0);
    m_v = axis*std::sin(angle/2.0);
}

void Quaternion::toAxisAngle(Vector &axis, double &angle) const {
    angle = 2*std::acos(m_s);
    if(std::abs(angle) > Constants::Epsilon) {
        axis = m_v / std::sin(angle/2.0);
    }
    /* No rotation, so there is no axis . . . */
    else axis = Vector();
}

Matrix Quaternion::toMatrix() const {
    Matrix matrix;

    double x = m_v.x();
    double y = m_v.y();
    double z = m_v.z();
    double s = m_s;
    
    matrix(0, 0) = 1 - 2*y*y - 2*z*z;
    matrix(0, 1) = 2*x*y - 2*z*s;
    matrix(0, 2) = 2*x*z + 2*y*s;
    matrix(0, 3) = 0;

    matrix(1, 0) = 2*x*y + 2*z*s;
    matrix(1, 1) = 1 - 2*x*x - 2*z*z;
    matrix(1, 2) = 2*y*z - 2*x*s;
    matrix(1, 3) = 0;

    matrix(2, 0)  = 2*x*z - 2*y*s;
    matrix(2, 1)  = 2*y*z + 2*x*s;
    matrix(2, 2) = 1 - 2*x*x - 2*y*y;
    matrix(2, 3) = 0;

    /*matrix(12] = 0;
    matrix(13] = 0;
    matrix(14] = 0;
    matrix(15] = 1;*/

    return matrix;
}

double Quaternion::angleTo(const Quaternion &other) const {
    double result = cosAngleTo(other);
    // fix numerical errors
    if(result > 1.0) result = 1.0;
    if(result < -1.0) result = -1.0;
    return std::acos(result);
}

double Quaternion::cosAngleTo(const Quaternion &other) const {
    Math::Vector x(1,0,0);
    return (*this * x).dot(other * x);
}

Quaternion Quaternion::slerp(const Quaternion &other, double by) const {
    auto angle = angleTo(other);
    if(std::fabs(angle) < Math::Constants::Epsilon) return other;

    if(by > angle) by = angle;

    double u = by / angle;

    double a = std::sin((1 - u) * angle) / std::sin(angle);
    double b = std::sin(u * angle) / std::sin(angle);
    Quaternion result(m_s * a + other.m_s * b,
        m_v * a + other.m_v * b);

    double length = std::sqrt(result.m_s*result.m_s + result.m_v.length2());
    result.m_s /= length;
    result.m_v /= length;

    return result;
}

}  // namespace Math
}  // namespace Kriti
