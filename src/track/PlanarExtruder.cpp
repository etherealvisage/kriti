#include <algorithm>

#include "PlanarExtruder.h"
#include "Partitioner.h"

#include "math/Quaternion.h"

#include "MessageSystem.h"

namespace Kriti {
namespace Track {

void PlanarExtruder::extrude(Node::Ptr root,
    std::vector<Math::Vector> &vertices, std::vector<Math::Vector> &normals,
    std::vector<unsigned int> &tris) {

    m_root = root;

    m_nmap.clear();

    m_pathList = Partitioner().partition(root);

    for(auto path : m_pathList) findPathProperties(path);

    generateNodeList();
    generateVertices();
    generateTris();
    generateNormals();

    // swap values into input references
    vertices.swap(m_vertices);
    normals.swap(m_normals);
    tris.swap(m_tris);

    Message3(Track, Log, "Extruded track has " << vertices.size()
        << " vertices and " << tris.size()/3 << " triangles.");

    // release memory given to data structures
    (decltype(m_pathList)()).swap(m_pathList);
    (decltype(m_tmap)()).swap(m_tmap);
    (decltype(m_nmap)()).swap(m_nmap);
    (decltype(m_nodeList)()).swap(m_nodeList);
    (decltype(m_vertices)()).swap(m_vertices);
    (decltype(m_normals)()).swap(m_normals);
    (decltype(m_tris)()).swap(m_tris);
}

void PlanarExtruder::findPathProperties(const std::vector<Node::Ptr> &path) {
    // special case: 2-element path; use 2-approximation of derivative.
    if(path.size() == 2) {
        Math::Vector v1 = path.front()->position();
        Math::Vector v2 = path.back()->position();
        Math::Vector tangent = (v1 + v2)/2;
        Math::Vector normal =
            Math::Vector(0.0, 1.0, 0.0).cross(tangent).normalized();
        // FIXME: don't overwrite old tangents/normals
        m_tmap[path.front()] = m_tmap[path.back()] = tangent;
        m_nmap[path.front()] = m_nmap[path.back()] = normal;
        return;
    }

    // Otherwise use 3-approximation.
    for(unsigned i = 1; i+1 < path.size(); i ++) {
        Math::Vector v1 = path[i-1]->position();
        Math::Vector v2 = path[i]->position();
        Math::Vector v3 = path[i+1]->position();

        Math::Vector tangent = (v1 + v2 + v2 + v3) / 4;
        Math::Vector normal =
            Math::Vector(0.0, 1.0, 0.0).cross(tangent).normalized();

        m_tmap[path[i]] = tangent;
        m_nmap[path[i]] = normal;
    }

    // Set path normals for special nodes if they haven't been set already.
    // Want to use incoming tangents for now.
    if(m_nmap.find(path.front()) == m_nmap.end()) {
        m_tmap[path.front()] = m_tmap[path[1]];
        m_nmap[path.front()] = m_nmap[path[1]];
    }
    if(m_nmap.find(path.back()) == m_nmap.end()) {
        m_tmap[path.back()] = m_tmap[path[path.size()-2]];
        m_nmap[path.back()] = m_nmap[path[path.size()-2]];
    }
}

void PlanarExtruder::generateNodeList() {
    std::vector<Node::Ptr> nodes;
    std::set<Node::Ptr> visited;
    nodes.push_back(m_root);
    while(nodes.size() > 0) {
        auto next = nodes.back();
        nodes.pop_back();

        if(visited.find(next) != visited.end()) continue;
        visited.insert(next);

        m_nodeList.push_back(next);

        for(auto n : next->next()) nodes.push_back(n);
    }
    Message3(Track, Debug, "Found " << m_nodeList.size() << " nodes.");
}

void PlanarExtruder::generateVertices() {
    m_vertices.clear();

    for(auto node : m_nodeList) {
        auto normal = m_nmap[node];
        Math::Vector proj(normal.x(), 0.0, normal.z());
        // TODO: calculate angle for banked curves
        double angle = 0.0;
        Math::Vector rproj =
            (Math::Quaternion(m_tmap[node], angle) * proj).normalized();

        // ensure we're pointing in the positive-x direction.
        if(rproj.x() < 0) rproj = -rproj;

        m_vertices.push_back(node->position() - rproj*m_width);
        m_vertices.push_back(node->position() + rproj*m_width);
    }
}

void PlanarExtruder::generateTris() {
    for(auto path : m_pathList) {
        for(unsigned i = 1; i < path.size(); i ++) {
            int i1 = std::binary_search(m_nodeList.begin(), m_nodeList.end(),
                path[i-1]);
            int i2 = std::binary_search(m_nodeList.begin(), m_nodeList.end(),
                path[i]);

            int v1 = i1*2, v2 = i1*2 + 1;
            int v3 = i2*2, v4 = i2*2 + 1;
            
            // Push both directions so that the track will be visible from
            // underneath.
            m_tris.push_back(v1);
            m_tris.push_back(v2);
            m_tris.push_back(v3);

            m_tris.push_back(v1);
            m_tris.push_back(v3);
            m_tris.push_back(v2);

            m_tris.push_back(v2);
            m_tris.push_back(v3);
            m_tris.push_back(v4);

            m_tris.push_back(v2);
            m_tris.push_back(v3);
            m_tris.push_back(v4);
        }
    }
}

void PlanarExtruder::generateNormals() {
    for(unsigned i = 0; i < m_tris.size(); i += 3) {
        auto v1 = m_vertices[m_tris[i]];
        auto v2 = m_vertices[m_tris[i+1]];
        auto v3 = m_vertices[m_tris[i+2]];
        auto n = (v2 - v1).cross(v3 - v1).normalized();
        m_normals.push_back(n);
        m_normals.push_back(n);
        m_normals.push_back(n);
    }
}

}  // namespace Track
}  // namespace Kriti
