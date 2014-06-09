#ifndef KRITI_SCENE__LIGHT_H
#define KRITI_SCENE__LIGHT_H

#include "math/Vector.h"

#include "render/Uniforms.h"

namespace Kriti {
namespace Scene {

class Light {
private:
    Math::Vector m_position, m_colour, m_falloff;
    float m_ambientCoefficient;
    float m_diffuseCoefficient;
    float m_specularCoefficient;
public:
    Light(Math::Vector position, Math::Vector colour, Math::Vector falloff,
        float ambientCoefficient, float diffuseCoefficient,
        float specularCoefficient) : m_position(position), m_colour(colour),
            m_falloff(falloff), m_ambientCoefficient(ambientCoefficient),
            m_diffuseCoefficient(diffuseCoefficient),
            m_specularCoefficient(specularCoefficient) {}

    Math::Vector position() const { return m_position; }
    void setPosition(const Math::Vector &position) { m_position = position; }
    Math::Vector colour() const { return m_colour; }
    Math::Vector falloff() const { return m_falloff; }
    float ambientCoefficient() const { return m_ambientCoefficient; }
    float diffuseCoefficient() const { return m_diffuseCoefficient; }
    float specularCoefficient() const { return m_specularCoefficient; }

    void setUniforms(Render::Uniforms &uniforms, int index,
        const Math::Matrix &transformation);
};

}  // namespace Scene
}  // namespace Kriti

#endif
