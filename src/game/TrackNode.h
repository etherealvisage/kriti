#ifndef KRITI_GAME__TRACK_NODE_H
#define KRITI_GAME__TRACK_NODE_H

#include <boost/shared_ptr.hpp>
#include <vector>

#include "math/Vector.h"

namespace Kriti {
namespace Game {

class TrackNode {
private:
    Math::Vector m_position;
    std::vector<boost::shared_ptr<TrackNode>> m_previous, m_next;
public:
    TrackNode(Math::Vector position) : m_position(position) {}

    Math::Vector position() const { return m_position; }

    const std::vector<boost::shared_ptr<TrackNode>> &previous() const
        { return m_previous; }
    void addPrevious(boost::shared_ptr<TrackNode> prev)
        { m_previous.push_back(prev); }
    void removePrevious(boost::shared_ptr<TrackNode> prev);

    const std::vector<boost::shared_ptr<TrackNode>> &next() const
        { return m_next; }
    void addNext(boost::shared_ptr<TrackNode> next) { m_next.push_back(next); }
    void removeNext(boost::shared_ptr<TrackNode> next);
};

}  // namespace Game
}  // namespace Kriti

#endif
