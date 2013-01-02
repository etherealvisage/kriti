#ifndef KRITI_TRACK__CLOSED_SUBDIVIDER_H
#define KRITI_TRACK__CLOSED_SUBDIVIDER_H

#include "Subdivider.h"

namespace Kriti {
namespace Track {

class ClosedSubdivider : public Subdivider {
private:
    int m_depth;
public:
    ClosedSubdivider(int depth);
    virtual ~ClosedSubdivider() {}

    virtual void subdivide(const std::vector<Node::Ptr> &path,
        Node::Ptr &nstart, Node::Ptr &nend);
private:
    void subdivide(std::vector<Math::Vector> &points);
};

}  // namespace Track
}  // namespace Kriti

#endif
