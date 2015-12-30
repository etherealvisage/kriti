#ifndef KRITI_SCENE__CAMERA_H
#define KRITI_SCENE__CAMERA_H

#include "../math/Vector.h"
#include "../math/Quaternion.h"
#include "../math/Matrix.h"

#include "../render/UniformHook.h"

#include "../TimeValue.h"

namespace Kriti {
namespace Scene {

class Camera : public Render::UniformHook {
public:
    enum PositionInterp {
        JumpPosition,
        LinearPosition,
        ExponentialPosition,
    };
    enum OrientationInterp {
        JumpOrientation,
        LinearOrientation,
        ExponentialOrientation,
    };
private:
    Math::Vector m_position;
    Math::Quaternion m_orientation;

    Math::Vector m_positionTarget;
    Math::Quaternion m_orientationTarget;

    Math::Matrix m_projection;

    PositionInterp m_positionInterp;
    OrientationInterp m_orientationInterp;

    double m_positionInterpFactor;
    double m_orientationInterpFactor;
public:
    Camera() : m_positionInterp(JumpPosition),
        m_orientationInterp(JumpOrientation), m_positionInterpFactor(1.0),
        m_orientationInterpFactor(1.0) {}

    void setInterpModes(PositionInterp pos, OrientationInterp orientation)
        { m_positionInterp = pos, m_orientationInterp = orientation; }
    void setPositionInterpFactor(double value)
        { m_positionInterpFactor = value; }
    void setOrientationInterpFactor(double value)
        { m_orientationInterpFactor = value; }

    Math::Vector position() const { return m_position; }
    Math::Quaternion orientation() const { return m_orientation; }

    Math::Vector targetPosition() const { return m_positionTarget; }
    Math::Quaternion targetOrientation() const { return m_orientationTarget; }

    void setProjection(Math::Matrix projection) { m_projection = projection; }

    Math::Matrix matrix() const;
    Math::Matrix matrixWithProjection() const;

    void setTarget(Math::Vector pos, Math::Quaternion orientation) 
        { m_positionTarget = pos, m_orientationTarget = orientation; }
    void step(TimeValue by);

    virtual void hook(Render::Uniforms &uniforms);
private:
    void stepPosition(TimeValue by);
    void stepOrientation(TimeValue by);
};

}  // namespace Scene
}  // namespace Kriti

#endif
