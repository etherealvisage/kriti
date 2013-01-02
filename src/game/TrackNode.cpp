#include "TrackNode.h"

namespace Kriti {
namespace GameTEMP {

void TrackNode::removePrevious(boost::shared_ptr<TrackNode> prev) {
    for(unsigned i = 0; i < m_previous.size(); i ++) {
        if(m_previous[i] == prev) {
            m_previous.erase(m_previous.begin() + i);
            break;
        }
    }
}

void TrackNode::removeNext(boost::shared_ptr<TrackNode> next) {
    for(unsigned i = 0; i < m_next.size(); i ++) {
        if(m_next[i] == next) {
            m_next.erase(m_next.begin() + i);
            break;
        }
    }
}

}  // namespace Game
}  // namespace Kriti
