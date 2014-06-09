#include "Camera.h"

#include "math/AffineTransformation.h"

namespace Kriti {
namespace Scene {

Math::Matrix Camera::matrix() const {
    Math::AffineTransformation at;
    at.translate(-m_position);
    Math::AffineTransformation at2;
    at2.rotate(Math::Point(), m_orientation);
    return at2.matrix() * at.matrix();
}

Math::Matrix Camera::matrixWithProjection() const {
    return m_projection * matrix();
}

void Camera::step(double time) {
    // just jump for now
    m_position = m_positionTarget;
    m_orientation = m_orientationTarget;
}

void Camera::hook(Render::Uniforms &uniforms) {
    uniforms.setParam("u_camera", matrixWithProjection());
}

}  // namespace Scene
}  // namespace Kriti
