#ifndef KRITI_MATH__AFFINE_TRANSFORMATION_H
#define KRITI_MATH__AFFINE_TRANSFORMATION_H

#include "Quaternion.h"
#include "Matrix.h"
#include "Vector.h"

namespace Kriti {
namespace Math {

class AffineTransformation {
private:
    Matrix m_transformation;
public:
    const Matrix &matrix() const { return m_transformation; }

    void translate(Vector by);
    void rotate(Point around, Quaternion by);
    void scale(Point around, double factor);
};

}  // namespace Math
}  // namespace Kriti

#endif
