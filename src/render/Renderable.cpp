#include "Renderable.h"
#include "math/AffineTransformation.h"

#include "MessageSystem.h"

namespace Kriti {
namespace Render {

void Renderable::addRenderSequence(
    boost::shared_ptr<RenderSequence> sequence) {
    
    m_sequences.push_back(sequence);
}

void Renderable::draw(const TechniqueParams &params) {
    Math::AffineTransformation at;
    at.translate(m_location);
    at.rotate(Math::Point(), m_orientation);
    Math::Matrix modelTransform = at.matrix();

    for(auto sequence : m_sequences) {
        sequence->draw(params, modelTransform);
    }
}

}  // namespace Render
}  // namespace Kriti
