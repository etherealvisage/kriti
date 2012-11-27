#include "Matrix.h"

namespace Kriti {
namespace Math {

Matrix::Matrix() {
    for(int i = 0; i < 16; i ++) {
        m_coefficients[i] = ((i % 5) == 0);
    }
}

Matrix Matrix::operator+(const Matrix &other) const {
    Matrix result;
    for(int i = 0; i < 16; i ++) {
        result.m_coefficients[i] = m_coefficients[i] + other.m_coefficients[i];
    }
    return result;
}

Matrix &Matrix::operator+=(const Matrix &other) {
    for(int i = 0; i < 16; i ++) {
        m_coefficients[i] += other.m_coefficients[i];
    }
    return *this;
}

Matrix Matrix::operator-(const Matrix &other) const {
    Matrix result;
    for(int i = 0; i < 16; i ++) {
        result.m_coefficients[i] = m_coefficients[i] - other.m_coefficients[i];
    }
    return result;
}

Matrix &Matrix::operator-=(const Matrix &other) {
    for(int i = 0; i < 16; i ++) {
        m_coefficients[i] -= other.m_coefficients[i];
    }
    return *this;
}

Vector Matrix::operator*(const Vector &other) const {
    Vector v;
    for(int i = 0; i < 4; i ++) {
        v[i] = m_coefficients[i*4+0]*other.x()
            + m_coefficients[i*4+1]*other.y()
            + m_coefficients[i*4+2]*other.z();
    }
    return v;
}

Point Matrix::operator*(const Point &other) const {
    Point p;
    for(int i = 0; i < 4; i ++) {
        p[i] = m_coefficients[i*4+0]*other.x()
            + m_coefficients[i*4+1]*other.y()
            + m_coefficients[i*4+2]*other.z()
            + m_coefficients[i*4+3];
    }
    return p;
}

}  // namespace Math
}  // namespace Kriti
