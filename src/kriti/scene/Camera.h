#ifndef KRITI_SCENE__CAMERA_H
#define KRITI_SCENE__CAMERA_H

#include "../math/Vector.h"
#include "../math/Quaternion.h"
#include "../math/Matrix.h"

#include "../render/UniformHook.h"

namespace Kriti {
namespace Scene {

class Camera : public Render::UniformHook {
private:
    Math::Vector m_position;
    Math::Quaternion m_orientation;

    Math::Vector m_positionTarget;
    Math::Quaternion m_orientationTarget;

    Math::Matrix m_projection;
public:
    Math::Vector position() const { return m_position; }
    Math::Quaternion orientation() const { return m_orientation; }

    void setProjection(Math::Matrix projection) { m_projection = projection; }

    Math::Matrix matrix() const;
    Math::Matrix matrixWithProjection() const;

    void setTarget(Math::Vector pos, Math::Quaternion orientation) 
        { m_positionTarget = pos, m_orientationTarget = orientation; }
    void step(double time);

    virtual void hook(Render::Uniforms &uniforms);
};

}  // namespace Scene
}  // namespace Kriti

#endif
