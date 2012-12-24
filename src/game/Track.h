#ifndef KRITI_GAME__TRACK_H
#define KRITI_GAME__TRACK_H

#include <boost/shared_ptr.hpp>

#include "TrackNode.h"

namespace Kriti {
namespace Game {

class Track {
private:
    boost::shared_ptr<TrackNode> m_rootNode;
public:
    Track() {}
    ~Track() {}

    void generateTrack();
private:
    void seedTrack();

    void subdivide(int levels);
    void performChaikin(int levels);
    void openChaikinHelper(std::vector<boost::shared_ptr<TrackNode>> path,
        boost::shared_ptr<TrackNode> &start,
        boost::shared_ptr<TrackNode> &end, int levels);

    void extrude();
};

}  // namespace Game
}  // namespace Kriti

#endif
