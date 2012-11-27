#include "Renderable.h"
#include "math/AffineTransformation.h"

namespace Kriti {
namespace Render {

void Renderable::addRenderSequence(
    boost::shared_ptr<RenderSequence> sequence) {
    
    m_sequences.push_back(sequence);
}

void Renderable::draw(const Math::Matrix &projection) {
    Math::AffineTransformation at;
    at.translate(m_location);
    at.rotate(Math::Point(), m_orientation);
    Math::Matrix modelTransform = at.matrix();

    for(auto sequence : m_sequences) {
        sequence->draw(projection, modelTransform);
    }
}

}  // namespace Render
}  // namespace Kriti
