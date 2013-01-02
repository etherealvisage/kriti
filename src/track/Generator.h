#ifndef KRITI_TRACK__GENERATOR_H
#define KRITI_TRACK__GENERATOR_H

#include <vector>

#include "Node.h"
#include "Subdivider.h"
#include "Extruder.h"

namespace Kriti {
namespace Track {

class Generator {
protected:
    Node::Ptr m_root;
    boost::shared_ptr<ExtrusionResult> m_result;
    std::vector<Math::Vector> m_vertices, m_normals;
    std::vector<unsigned int> m_tris;
public:
    Generator() {}
    virtual ~Generator() {}

    boost::shared_ptr<ExtrusionResult> generate(Subdivider *subdivider,
        Extruder *extruder);
protected:
    virtual void seed();
    virtual void build() = 0;
    void subdivide(Subdivider *subdivider);
    void extrude(Extruder *extruder);
};

}  // namespace Track
}  // namespace Kriti

#endif
