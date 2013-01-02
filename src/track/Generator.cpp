#include <boost/make_shared.hpp>

#include "Generator.h"
#include "Partitioner.h"

#include "MessageSystem.h"

namespace Kriti {
namespace Track {

void Generator::generate(Subdivider *subdivider, Extruder *extruder) {
    seed();
    build();
    subdivide(subdivider);
    extrude(extruder);
}

void Generator::seed() {
    m_root = boost::make_shared<Node>(Math::Vector());
    auto initial = boost::make_shared<Node>(
        Math::Vector(0.0, 0.0, -50.0));

    m_root->addNext(initial);
    initial->addPrev(m_root);
}

void Generator::subdivide(Subdivider *subdivider) {
    Track::Partitioner partitioner;
    auto paths = partitioner.partition(m_root);
    for(auto path : paths) {
        Message3(Track, Debug, "Path length: " << path.size());
        Node::Ptr nstart, nend;
        subdivider->subdivide(path, nstart, nend);
    }
}

void Generator::extrude(Extruder *extruder) {
    std::vector<Math::Vector> vert, norm;
    std::vector<unsigned int> tris;
    extruder->extrude(m_root, vert, norm, tris);
}

}  // namespace Track
}  // namespace Kriti
