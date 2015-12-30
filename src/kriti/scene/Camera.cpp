#include "Camera.h"

#include "../math/AffineTransformation.h"

#include "../MessageSystem.h"

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

void Camera::step(TimeValue by) {
    stepPosition(by);
    stepOrientation(by);
}

void Camera::hook(Render::Uniforms &uniforms) {
    uniforms.setParam("u_camera", matrixWithProjection());
}

void Camera::stepPosition(TimeValue by) {
    auto delta = m_positionTarget - m_position;
    auto distance = delta.length();
    auto tdelta = (by.toUsec() / 1.0e6);

    switch(m_positionInterp) {
    case JumpPosition:
        m_position = m_positionTarget;
        break;
    case LinearPosition: {
        auto step = m_positionInterpFactor * tdelta;
        if(distance <= step) step = distance;

        m_position += delta.normalized() * step;
        break;
    }
    case ExponentialPosition: {
        // factor: average movement speed?
        auto step = distance * std::pow(0.5, tdelta) * m_positionInterpFactor;
        if(distance <= step) step = distance;

        m_position += delta.normalized() * step;
        break;
    }
    default:
        Message3(Scene, Fatal, "Unknown camera position interpolation type!");
        break;
    }
}

void Camera::stepOrientation(TimeValue by) {
    auto distance = m_orientation.angleTo(m_orientationTarget);
    if(distance == 0) return;

    auto tdelta = (by.toUsec() / 1.0e6);

    switch(m_orientationInterp) {
    case JumpOrientation:
        m_orientation = m_orientationTarget;
        break;
    case LinearOrientation: {
        auto step = m_orientationInterpFactor * tdelta;
        if(step > distance) step = distance;

        m_orientation = m_orientation.slerp(m_orientationTarget, step);
        break;
    }
    case ExponentialOrientation: {
        // factor: average movement speed?
        auto step =
            distance * std::pow(0.5, tdelta) * m_orientationInterpFactor;
        if(distance <= step) step = distance;

        m_orientation = m_orientation.slerp(m_orientationTarget, step);
        break;
    }
    default:
        Message3(Scene, Fatal, "Unknown camera orientation interpolation type!");
        break;
    }
}

}  // namespace Scene
}  // namespace Kriti
