#include "Light.h"

#include "StreamAsString.h"

namespace Kriti {
namespace Scene {

void Light::setUniforms(Render::Uniforms &uniforms, int index,
    const Math::Matrix &transformation) {

    std::string base = StreamAsString() << "lights[" << index << "].";

    uniforms.setParam(base + "position",
        transformation * Math::Point(m_position));
    uniforms.setParam(base + "falloff", m_falloff);
    uniforms.setParam(base + "colour", m_colour);
    uniforms.setParam(base + "ambientCoefficient", m_ambientCoefficient);
    uniforms.setParam(base + "diffuseCoefficient", m_diffuseCoefficient);
    uniforms.setParam(base + "specularCoefficient", m_specularCoefficient);
}

}  // namespace Scene
}  // namespace Kriti
