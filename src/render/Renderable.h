#ifndef KRITI_RENDER__RENDERABLE_H
#define KRITI_RENDER__RENDERABLE_H

#include <vector>

#include "RenderSequence.h"

#include "math/Vector.h"
#include "math/Quaternion.h"

namespace Kriti {
namespace Render {

class Renderable {
private:
    std::vector<boost::shared_ptr<RenderSequence>> m_sequences;
    Math::Vector m_location;
    Math::Quaternion m_orientation;
public:
    Renderable();
    ~Renderable();

    void addRenderSequence(boost::shared_ptr<RenderSequence> sequence);

    void draw();

    Math::Vector &location() { return m_location; }
    Math::Quaternion &orientation() { return m_orientation; }
};

}  // namespace Render
}  // namespace Kriti

#endif
