#ifndef KRITI_MATH__VIEW_GENERATOR_H
#define KRITI_MATH__VIEW_GENERATOR_H

#include "Matrix.h"

namespace Kriti {
namespace Math {

class ViewGenerator {
public:
    Matrix frustum(double left, double right, double top, double bottom,
        double near, double far);
    Matrix perspective(double fov, double ratio, double near, double far);

    // sets up orthogonal projection, left is (-width/2) etc.
    Matrix orthogonal(double width, double height, double near, double far);
};

}  // namespace Math
}  // namespace Kriti

#endif
