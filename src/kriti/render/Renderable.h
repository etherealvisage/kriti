#ifndef KRITI_RENDER__RENDERABLE_H
#define KRITI_RENDER__RENDERABLE_H

#include <vector>

#include "RenderSequence.h"
#include "Uniforms.h"

#include "../math/Vector.h"
#include "../math/Quaternion.h"
#include "../math/Matrix.h"

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
    const Math::Vector &location() const { return m_location; }
    void setLocation(const Math::Vector &to) { m_location = to; }

    double &scale() { return m_scale; }
    double scale() const { return m_scale; }
    void setScale(double to) { m_scale = to; }

    Math::Quaternion &orientation() { return m_orientation; }
    const Math::Quaternion &orientation() const { return m_orientation; }
    void setOrientation(const Math::Quaternion &to) { m_orientation = to; }
};

}  // namespace Render
}  // namespace Kriti

#endif
