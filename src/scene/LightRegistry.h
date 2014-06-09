#ifndef KRITI_SCENE__LIGHT_REGISTRY_H
#define KRITI_SCENE__LIGHT_REGISTRY_H

#include <boost/shared_ptr.hpp>

#include "Light.h"

#include "render/UniformHook.h"

#include "Camera.h"

namespace Kriti {
namespace Scene {

class LightRegistry : public Render::UniformHook {
private:
    std::vector<boost::shared_ptr<Light>> m_lights;
    boost::shared_ptr<Camera> m_camera;
public:
    void add(boost::shared_ptr<Light> light);
    void remove(boost::shared_ptr<Light> light);

    void setCamera(boost::shared_ptr<Camera> camera) { m_camera = camera; }

    virtual void hook(Render::Uniforms &uniforms);
};

}  // namespace Scene
}  // namespace Kriti

#endif
