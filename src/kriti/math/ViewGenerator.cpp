#include <cmath>

#include "ViewGenerator.h"

namespace Kriti {
namespace Math {

Matrix ViewGenerator::frustum(double left, double right, double top,
    double bottom, double near, double far) {
    
    Matrix result;
    result(3,3) = 0.0;

    result(0,0) = (2 * near) / (right - left);
    result(1,1) = (2 * near) / (top - bottom);
    result(0,2) = (right + left) / (right - left);
    result(1,2) = (top + bottom) / (top - bottom);
    result(2,2) = -((far + near)/(far - near));
    result(3,2) = -1.0;
    result(2,3) = -((2*far*near)/(far - near));

    return result;
}

Matrix ViewGenerator::perspective(double fov, double ratio, double near,
    double far) {
    
    fov /= 2;
    double range = std::tan(fov) * near;

    double left = -range*ratio;
    double right = range*ratio;
    double top = range;
    double bottom = -range;

    return frustum(left, right, top, bottom, near, far);
}

Matrix ViewGenerator::orthogonal(double width, double height, double near,
    double far) {

    return orthogonal(-width/2, width/2, -height/2, height/2, near, far);
}

Matrix ViewGenerator::orthogonal(double left, double right, double top,
    double bottom, double near, double far) {

    Matrix result;

    result(0,0) = 2/(right-left);
    result(0,3) = -(right+left)/(right-left);
    result(1,1) = 2/(top-bottom);
    result(1,3) = -(top+bottom)/(top-bottom);
    result(2,2) = -2/(far-near);
    result(3,2) = -(far+near)/(far-near);
    result(3,3) = 1.0;

    return result;
}

}  // namespace Math
}  // namespace Kriti
