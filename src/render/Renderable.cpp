#include "Renderable.h"

namespace Kriti {
namespace Render {

void Renderable::addRenderSequence(
    boost::shared_ptr<RenderSequence> sequence) {
    
    m_sequences.push_back(sequence);
}

void Renderable::draw() {
    
}

}  // namespace Render
}  // namespace Kriti
