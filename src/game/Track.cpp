#include <vector>
#include <set>
#include <queue>
#include <map>

#include <boost/make_shared.hpp>

#include "Track.h"
#include "MessageSystem.h"

namespace Kriti {
namespace Game {

void Track::generateTrack() {
    seedTrack();

    //randomizeTrack();

    subdivide(8);
    extrude();
}

void Track::seedTrack() {
    m_rootNode = boost::shared_ptr<TrackNode>(
        new TrackNode(Math::Vector(0.0, 0.0, 0.0)));

    auto second = boost::shared_ptr<TrackNode>(
        new TrackNode(Math::Vector(-100.0, 0.0, 100.0)));

    auto third = boost::shared_ptr<TrackNode>(
        new TrackNode(Math::Vector(100.0, 0.0, 200.0)));

    m_rootNode->addNext(second);

    second->addPrevious(m_rootNode);
    second->addNext(third);

    third->addPrevious(second);
}

void Track::subdivide(int levels) {
    for(int i = 0; i < levels; i ++) performChaikin();
}

void Track::performChaikin() {
    /* perform basic sanity-check and find initial node mapping. */
    if(m_rootNode->previous().size() > 0) Message3(Game, Fatal,
        "Root node has previous node(s).");
    if(m_rootNode->next().size() > 1) Message3(Game, Fatal,
        "Root node has multiple next nodes.");

    std::map<boost::shared_ptr<TrackNode>, boost::shared_ptr<TrackNode>> nmap;
    std::vector<std::vector<TrackNodePtr>> paths;

    paths = findPaths();

    bool first = true;
    for(auto path : paths) {
        TrackNodePtr nstart, nend;
        openChaikinHelper(path, nmap, nstart, nend);

        if(first) {
            if(path.front() == m_rootNode) {
                m_rootNode = nstart;
            }
            else {
                nmap[path.front()]->addNext(nstart);
            }

            first = false;
        }
        else {
            nmap[path.front()]->addNext(nstart);
            nmap[path.back()]->addPrevious(nend);
        }
    }
}

void Track::openChaikinHelper(std::vector<boost::shared_ptr<TrackNode>> path,
    std::map<TrackNodePtr, TrackNodePtr> &nodeMap,
    boost::shared_ptr<TrackNode> &start, boost::shared_ptr<TrackNode> &end) {

    std::vector<TrackNodePtr> newPath;
    Message3(Game, Debug, "Subdividing path of size " << path.size());
    for(unsigned i = 0; i < path.size()-1; i ++) {
        Math::Vector p1 = path[i]->position();
        Math::Vector p2 = path[i+1]->position();

        Math::Vector np1 = 0.75*p1 + 0.25*p2;
        Math::Vector np2 = 0.25*p1 + 0.75*p2;

        newPath.push_back(boost::make_shared<TrackNode>(np1));
        newPath.push_back(boost::make_shared<TrackNode>(np2));

        if(path[i]->previous().size() > 1) {
            nodeMap[path[i]] = newPath[newPath.size()-2];
        }
        if(path[i+1]->next().size() > 1) {
            nodeMap[path[i+1]] = newPath[newPath.size()-1];
        }
    }

    for(unsigned i = 0; i < newPath.size(); i ++) {
        if(i > 0)
            newPath[i]->addPrevious(newPath[i-1]);
        if(i < newPath.size()-1)
            newPath[i]->addNext(newPath[i+1]);
    }

    start = newPath.front();
    end = newPath.back();
}

void Track::extrude() {
    std::map<TrackNodePtr, Math::Vector> curveNormals;

    auto list = findPaths();

    for(auto path : list) {
        if(path.size() == 0) {
            Message3(Game, Fatal, "Zero-length path found while extruding.");
        }

        for(unsigned i = 1; i < path.size()-1; i ++) {
            Math::Vector v1 = (path[i]->position()
                - path[i-1]->position()).normalized();
            Math::Vector v2 = (path[i+1]->position()
                - path[i]->position()).normalized();
            Math::Vector tangent = (v1+v2)/2;

            Math::Vector normal = tangent.cross(Math::Vector(0.0, 1.0, 0.0));
            if(normal.length() < 1e-5) {
                normal = Math::Vector(0.0, 0.0, 1.0);
            }

            curveNormals[path[i]] = normal;
        }
    }

    for(auto path : list) {
        
    }
}

std::vector<std::vector<TrackNodePtr>> Track::findPaths() {
    std::vector<std::vector<TrackNodePtr>> paths;

    std::vector<boost::shared_ptr<TrackNode>> nodes;
    std::set<boost::shared_ptr<TrackNode>> visited;
    nodes.push_back(m_rootNode);
    TrackNodePtr start;
    std::vector<TrackNodePtr> path;
    bool reset = true;

    while(nodes.size() > 0) {
        auto node = nodes.front();
        nodes.pop_back();

        if(reset) {
            reset = false;
            path.clear();
        }
        path.push_back(node);

        if(visited.find(node) != visited.end()) {
            if(node == path.front()) reset = true;
            else {
                paths.push_back(path);
                reset = true;
            }
            continue;
        }
        visited.insert(node);

        if(node->previous().size() > 1 && node->next().size() > 1) {
            Message3(Game, Fatal, "Node with multiple incoming and "
                "multiple outgoing!");
        }

        for(unsigned i = 0; i < node->next().size(); i ++) {
            nodes.push_back(node->next()[i]);
        }

        if(node->next().size() == 0) {
            paths.push_back(path);
            reset = true;
        }
    }

    return paths;
}

}  // namespace Game
}  // namespace Kriti
