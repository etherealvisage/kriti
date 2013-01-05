#include "SceneCamera.h"

#include "math/AffineTransformation.h"

namespace Kriti {
namespace Render {

Math::Matrix SceneCamera::matrix() const {
    Math::AffineTransformation at;
    at.translate(-m_position);
    Math::AffineTransformation at2;
    at2.rotate(Math::Point(), m_orientation);
    return m_projection * at2.matrix() * at.matrix();
}

void SceneCamera::step(double time) {
    // just jump for now
    m_position = m_positionTarget;
    m_orientation = m_orientationTarget;
}

}  // namespace Render
}  // namespace Kriti
