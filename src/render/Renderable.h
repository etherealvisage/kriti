#ifndef KRITI_RENDER__RENDERABLE_H
#define KRITI_RENDER__RENDERABLE_H

#include <vector>

#include "RenderSequence.h"
#include "Uniforms.h"

#include "math/Vector.h"
#include "math/Quaternion.h"
#include "math/Matrix.h"

namespace Kriti {
namespace Render {

class Renderable {
private:
    std::vector<boost::shared_ptr<RenderSequence>> m_sequences;
    Math::Vector m_location;
    double m_scale;
    Math::Quaternion m_orientation;
public:
    Renderable() : m_scale(1.0) {}

    void addRenderSequence(boost::shared_ptr<RenderSequence> sequence);
    boost::shared_ptr<RenderSequence> renderSequence(int which) const
        { return m_sequences[which]; }
    int renderSequenceCount() const { return m_sequences.size(); }
    void clearRenderSequences() { m_sequences.clear(); }

    void draw(const Uniforms &params,
        std::map<boost::weak_ptr<Material>, Uniforms> &materialParams);

    Math::Vector &location() { return m_location; }
    double &scale() { return m_scale; }
    Math::Quaternion &orientation() { return m_orientation; }
};

}  // namespace Render
}  // namespace Kriti

#endif
