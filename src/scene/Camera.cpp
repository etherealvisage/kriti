#include "Camera.h"

#include "math/AffineTransformation.h"

namespace Kriti {
namespace Scene {

Math::Matrix Camera::matrix() const {
    Math::AffineTransformation at;
    at.translate(-m_position);
    Math::AffineTransformation at2;
    at2.rotate(Math::Point(), m_orientation);
    return m_projection * at2.matrix() * at.matrix();
}

void Camera::step(double time) {
    // just jump for now
    m_position = m_positionTarget;
    m_orientation = m_orientationTarget;
}

void Camera::hook(Render::Uniforms &uniforms) {
    uniforms.setParam("u_camera", matrix());
}

}  // namespace Scene
}  // namespace Kriti
