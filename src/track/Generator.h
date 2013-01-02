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
    std::vector<Math::Vector> m_vertices, m_normals;
    std::vector<unsigned int> m_tris;
public:
    Generator() {}
    virtual ~Generator() {}

    void generate(Subdivider *subdivider, Extruder *extruder);
    /** Retrieve the results of the curve extrusion.
        IMPORTANT: this function will destroy the internal representation of
        the geometry!
    */
    void getExtrusion(std::vector<Math::Vector> &vertices,
        std::vector<Math::Vector> &normals, std::vector<unsigned int> &tris) {
        
        vertices.swap(m_vertices);
        normals.swap(m_normals);
        tris.swap(m_tris);
    }
protected:
    virtual void seed();
    virtual void build() = 0;
    void subdivide(Subdivider *subdivider);
    void extrude(Extruder *extruder);
};

}  // namespace Track
}  // namespace Kriti

#endif
