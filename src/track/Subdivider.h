#ifndef KRITI_TRACK__SUBDIVIDER_H
#define KRITI_TRACK__SUBDIVIDER_H

#include <vector>

#include "Node.h"

namespace Kriti {
namespace Track {

class Subdivider {
public:
    virtual ~Subdivider() {}

    virtual void subdivide(const std::vector<Node::Ptr> &path,
        Node::Ptr &nstart, Node::Ptr &nend) = 0;
};

}  // namespace Track
}  // namespace Kriti

#endif
