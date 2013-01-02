#ifndef KRITI_TRACK__NODE_H
#define KRITI_TRACK__NODE_H

#include <boost/shared_ptr.hpp>

#include "math/Vector.h"

namespace Kriti {
namespace Track {

class Node {
public:
    typedef boost::shared_ptr<Node> Ptr;
private:
    Math::Vector m_position;
    std::vector<Ptr> m_next, m_prev;
public:
    Node(Math::Vector position) : m_position(position) {}

    Math::Vector position() const { return m_position; }

    void addNext(Ptr p) { m_next.push_back(p); }
    std::vector<Ptr> &next() { return m_next; }
    void addPrev(Ptr p) { m_prev.push_back(p); }
    std::vector<Ptr> &prev() { return m_prev; }
};

}  // namespace Track
}  // namespace Kriti

#endif
