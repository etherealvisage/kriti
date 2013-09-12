#include <GL/glew.h>

#include "Renderable.h"
#include "math/AffineTransformation.h"

#include "MessageSystem.h"

namespace Kriti {
namespace Render {

void Renderable::addRenderSequence(
    boost::shared_ptr<RenderSequence> sequence) {
    
    m_sequences.push_back(sequence);
}

void Renderable::draw(const Uniforms &params,
    std::map<boost::weak_ptr<Material>, Uniforms> &materialParams) {

    Math::AffineTransformation at;
    at.scale(Math::Point(), m_scale);
    at.rotate(Math::Point(), m_orientation);
    at.translate(m_location);
    Math::Matrix modelTransform = at.matrix();

    for(auto sequence : m_sequences) {
        sequence->draw(params, materialParams, modelTransform);
    }
}

}  // namespace Render
}  // namespace Kriti
