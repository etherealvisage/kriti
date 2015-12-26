#include "Matrix.h"

#include "Vector.h"

namespace Kriti {
namespace Math {

Matrix::Matrix() {
    for(int i = 0; i < 16; i ++) {
        m_coefficients[i] = ((i % 5) == 0) ? 1 : 0;
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

Matrix Matrix::operator*(const Matrix &other) const {
    Matrix m;
    for(int i = 0; i < 4; i ++) {
        for(int j = 0; j < 4; j ++) {
            m(i, j) = (*this)(i, 0)*other(0, j)
                + (*this)(i, 1)*other(1, j)
                + (*this)(i, 2)*other(2, j)
                + (*this)(i, 3)*other(3, j);
        }
    }
    return m;
}

Matrix &Matrix::operator*=(const Matrix &other) {
    *this = *this * other;
    return *this;
}

Matrix Matrix::operator*(double factor) const {
    Matrix result = *this;
    for(int i = 0; i < 16; i ++) result.m_coefficients[i] *= factor;
    return result;
}

Matrix &Matrix::operator*=(double factor) {
    for(int i = 0; i < 16; i ++) m_coefficients[i] *= factor;
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
    double pc[4];
    for(int i = 0; i < 4; i ++) {
        pc[i] = m_coefficients[i*4+0]*other.x()
            + m_coefficients[i*4+1]*other.y()
            + m_coefficients[i*4+2]*other.z()
            + m_coefficients[i*4+3];
    }
    return Point(pc[0]/pc[3],pc[1]/pc[3],pc[2]/pc[3]);
}

}  // namespace Math
}  // namespace Kriti
