#include <vector>
#include <set>
#include <queue>
#include <map>

#include "Track.h"
#include "MessageSystem.h"

namespace Kriti {
namespace Game {

void Track::generateTrack() {
    seedTrack();

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
    for(int i = 0; i < levels; i ++) performChaikin(levels);
}

void Track::performChaikin(int levels) {
    /* perform basic sanity-check and find initial node mapping. */
    if(m_rootNode->previous().size() > 1) Message3(Game, Fatal,
        "Root node has multiple previous nodes.");
    if(m_rootNode->next().size() > 1) Message3(Game, Fatal,
        "Root node has multiple next nodes.");

    std::map<boost::shared_ptr<TrackNode>, int> nodeMap;
    std::map<int, boost::shared_ptr<TrackNode>> rnodeMap;
    std::map<int, std::vector<int>> edges;

    int lastNode = 0;
    std::queue<boost::shared_ptr<TrackNode>> nodes;
    nodes.push(m_rootNode);
    while(nodes.size() > 0) {
        auto node = nodes.front();
        nodes.pop();
        
        if(nodeMap[node] != 0) continue;
        nodeMap[node] = ++lastNode;
        rnodeMap[lastNode] = node;

        if(node->previous().size() > 1 && node->next().size() > 1) {
            Message3(Game, Fatal, "Node with multiple incoming and "
                "multiple outgoing!");
        }

        for(unsigned i = 0; i < node->next().size(); i ++) {
            nodes.push(node->next()[i]);
        }
    }

    std::set<boost::shared_ptr<TrackNode>> visited;
    nodes.push(m_rootNode);
    while(nodes.size() > 0) {
        auto node = nodes.front();
        nodes.pop();
        
        if(visited.find(node) != visited.end()) continue;
        visited.insert(node);

        for(unsigned i = 0; i < node->next().size(); i ++) {
            nodes.push(node->next()[i]);
            edges[nodeMap[node]].push_back(nodeMap[node->next()[i]]);
            edges[nodeMap[node->next()[i]]].push_back(nodeMap[node]);
        }
    }

    // collapse nodes as necessary.
    for(int i = 0; i < lastNode; i ++) {
        if(edges[i].size() == 2) {
            // collapse node
            *std::find(edges[edges[i][0]].begin(), 
                edges[edges[i][0]].end(), i) = edges[i][1];
            *std::find(edges[edges[i][1]].begin(), 
                edges[edges[i][1]].end(), i) = edges[i][0];
        }
    }
}

void Track::openChaikinHelper(std::vector<boost::shared_ptr<TrackNode>> path,
    boost::shared_ptr<TrackNode> &start, boost::shared_ptr<TrackNode> &end,
    int levels) {

}

void Track::extrude() {
    
}

}  // namespace Game
}  // namespace Kriti
