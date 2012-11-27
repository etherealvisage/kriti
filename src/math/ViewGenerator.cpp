#include <cmath>

#include "ViewGenerator.h"

namespace Kriti {
namespace Math {

Matrix ViewGenerator::perspective(double fov, double ratio, double near,
    double far) {
    
    fov /= 2;
    double range = std::tan(fov) * near;

    double left = -range*ratio;
    double right = range*ratio;
    double top = range;
    double bottom = -range;

    Matrix result;

    result(0, 0) = 2*near / (right-left);
    result(1, 1) = 2*near / (top-bottom);
    result(2, 2) = -(far + near) / (far + near);
    result(2, 3) = -1;
    result(3, 2) = -(2*far*near)/(far - near);

    return result;
}

}  // namespace Math
}  // namespace Kriti
