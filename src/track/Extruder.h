#ifndef KRITI_TRACK__EXTRUDER_H
#define KRITI_TRACK__EXTRUDER_H

#include <utility>

#include "Node.h"

namespace Kriti {
namespace Track {

class Extruder {
public:
    virtual void extrude(Node::Ptr root,
        std::vector<Math::Vector> &vertices,
        std::vector<Math::Vector> &normals,
        std::vector<unsigned int> &tris) = 0;
};

}  // namespace Track
}  // namespace Kriti

#endif
