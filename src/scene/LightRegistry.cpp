#include "LightRegistry.h"

namespace Kriti {
namespace Scene {

void LightRegistry::add(boost::shared_ptr<Light> light) {
    m_lights.push_back(light);
}

void LightRegistry::remove(boost::shared_ptr<Light> light) {
    for(auto &l : m_lights) {
        if(l != light) continue;
        std::swap(l, m_lights.back());
        m_lights.pop_back();
        break;
    }
}

void LightRegistry::hook(Render::Uniforms &uniforms) {
    for(int i = 0; i < m_lights.size(); i ++) {
        m_lights[i]->setUniforms(uniforms, i);
    }
    uniforms.setParam("lightCount", static_cast<int>(m_lights.size()));
}

}  // namespace Scene
}  // namespace Kriti
