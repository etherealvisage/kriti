#ifndef KRITI_GAME__TRACK_H
#define KRITI_GAME__TRACK_H

#include <boost/shared_ptr.hpp>

#include "TrackNode.h"

namespace Kriti {
namespace Game {

class Track {
private:
    TrackNodePtr m_rootNode;
    std::vector<Math::Vector> m_geometry;
public:
    Track() {}
    ~Track() {}

    void generateTrack();
    const std::vector<Math::Vector> &geometry() const { return m_geometry; }
private:
    void seedTrack();

    void subdivide(int levels);
    void performChaikin();
    void openChaikinHelper(std::vector<TrackNodePtr> path,
        std::map<TrackNodePtr, TrackNodePtr> &nodeMap, TrackNodePtr &start,
        TrackNodePtr &end);

    void extrude();
private:
    std::vector<std::vector<TrackNodePtr>> findPaths();
};

}  // namespace Game
}  // namespace Kriti

#endif
