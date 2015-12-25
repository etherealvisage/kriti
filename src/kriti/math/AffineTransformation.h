#ifndef KRITI_MATH__AFFINE_TRANSFORMATION_H
#define KRITI_MATH__AFFINE_TRANSFORMATION_H

#include "Matrix.h"
#include "Quaternion.fwd"
#include "Vector.fwd"

namespace Kriti {
namespace Math {

class AffineTransformation {
private:
    Matrix m_transformation;
public:
    const Matrix &matrix() const { return m_transformation; }

    void translate(Vector by);
    void rotate(const Point &around, const Quaternion &by);
    void scale(const Point &around, double factor);
};

}  // namespace Math
}  // namespace Kriti

#endif
