#ifndef KRITI_RENDER__SCENE_CAMERA_H
#define KRITI_RENDER__SCENE_CAMERA_H

#include "math/Vector.h"
#include "math/Quaternion.h"
#include "math/Matrix.h"

namespace Kriti {
namespace Render {

class SceneCamera {
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

    void setTarget(Math::Vector pos, Math::Quaternion orientation) 
        { m_positionTarget = pos, m_orientationTarget = orientation; }
    void step(double time);
};

}  // namespace Render
}  // namespace Kriti

#endif
