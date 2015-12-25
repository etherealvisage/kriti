#include "AffineTransformation.h"

#include "Quaternion.h"
#include "Vector.h"

namespace Kriti {
namespace Math {

void AffineTransformation::translate(Vector by) {
    m_transformation(0, 3) += by.x();
    m_transformation(1, 3) += by.y();
    m_transformation(2, 3) += by.z();
}

void AffineTransformation::rotate(const Point &around, const Quaternion &by) {
    translate(-around);
    m_transformation *= by.toMatrix();
    translate(around);
}

void AffineTransformation::scale(const Point &around, double factor) {
    translate(-around);
    m_transformation *= factor;
    translate(around);
    m_transformation(3,3) = 1.0;
}

}  // namespace Math
}  // namespace Kriti
