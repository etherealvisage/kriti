#ifndef KRITI_MATH__MATRIX_H
#define KRITI_MATH__MATRIX_H

#include "Vector.h"

namespace Kriti {
namespace Math {

class Matrix {
private:
    float m_coefficients[16];
public:
    Matrix();

    const float * matrixData() const { return m_coefficients; }

    float &operator()(int i, int j) {
        return m_coefficients[i + j*4];
    }

    float operator()(int i, int j) const {
        return m_coefficients[i + j*4];
    }

    Matrix operator+(const Matrix &other) const;
    Matrix &operator+=(const Matrix &other);
    Matrix operator-(const Matrix &other) const;
    Matrix &operator-=(const Matrix &other);

    Matrix operator*(const Matrix &other) const;
    Matrix &operator*=(const Matrix &other);

    Matrix operator*(double factor) const;
    Matrix &operator*=(double factor);

    Vector operator*(const Vector &other) const;
    Point operator*(const Point &other) const;
};

}  // namespace Math
}  // namespace Kriti

#endif
