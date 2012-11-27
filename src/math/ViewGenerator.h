#ifndef KRITI_MATH__VIEW_GENERATOR_H
#define KRITI_MATH__VIEW_GENERATOR_H

#include "Matrix.h"

namespace Kriti {
namespace Math {

class ViewGenerator {
public:
    Matrix perspective(double fov, double ratio, double near, double far);
};

}  // namespace Math
}  // namespace Kriti

#endif
