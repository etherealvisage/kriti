#include "AffineTransformation.h"

namespace Kriti {
namespace Math {

void AffineTransformation::translate(Vector by) {
    m_transformation(3, 0) += by.x();
    m_transformation(3, 1) += by.y();
    m_transformation(3, 2) += by.z();
}

void AffineTransformation::rotate(Point around, Quaternion by) {
    translate(-around);
    m_transformation *= by.toMatrix();
    translate(around);
}

void AffineTransformation::scale(Point around, double factor) {
    translate(-around);
    m_transformation *= factor;
    translate(around);
}

}  // namespace Math
}  // namespace Kriti
