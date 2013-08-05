#include <algorithm>

#include <boost/make_shared.hpp>

#include "CylindricExtruder.h"
#include "Partitioner.h"

#include "math/Quaternion.h"

#include "MessageSystem.h"

namespace Kriti {
namespace Track {

boost::shared_ptr<ExtrusionResult> CylindricExtruder::extrude(Node::Ptr root) {
    m_root = root;

    m_nmap.clear();

    m_pathList = Partitioner().partition(root);

    for(auto path : m_pathList) findPathProperties(path);

    generateNodeList();
    generateVertices();
    generateTris();
    generateNormals();
    generateTexs();

    // swap values into input references
    auto ret = boost::make_shared<ExtrusionResult>(m_vertices, m_normals,
        m_texs, m_tris);

    // release memory given to data structures
    (decltype(m_pathList)()).swap(m_pathList);
    (decltype(m_tmap)()).swap(m_tmap);
    (decltype(m_nmap)()).swap(m_nmap);
    (decltype(m_nodeList)()).swap(m_nodeList);
    (decltype(m_vertices)()).swap(m_vertices);
    (decltype(m_normals)()).swap(m_normals);
    (decltype(m_tris)()).swap(m_tris);

    return ret;
}

void CylindricExtruder::findPathProperties(const std::vector<Node::Ptr> &path) {
    // special case: 2-element path; use 2-approximation of derivative.
    if(path.size() == 2) {
        Math::Vector v1 = path.front()->position();
        Math::Vector v2 = path.back()->position();
        Math::Vector tangent = (v1 + v2)/2;
        Math::Vector normal =
            Math::Vector(0.0, 1.0, 0.0).cross(tangent).normalized();
        // FIXME: don't overwrite old tangents/normals
        m_tmap[path.front()] = m_tmap[path.back()] = tangent.normalized();
        m_nmap[path.front()] = m_nmap[path.back()] = normal.normalized();
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

        m_tmap[path[i]] = tangent.normalized();
        m_nmap[path[i]] = normal.normalized();
        //Message3(Track, Debug, "Normal: " << normal.toString());
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

void CylindricExtruder::generateNodeList() {
    m_nodeList.clear();
    m_nodeIndices.clear();
    std::vector<Node::Ptr> nodes;
    std::set<Node::Ptr> visited;
    nodes.push_back(m_root);
    while(nodes.size() > 0) {
        auto next = nodes.back();
        nodes.pop_back();

        if(visited.find(next) != visited.end()) continue;
        visited.insert(next);

        m_nodeList.push_back(next);
        m_nodeIndices[next] = m_nodeList.size()-1;

        for(auto n : next->next()) nodes.push_back(n);
    }
    Message3(Track, Debug, "Found " << m_nodeList.size() << " nodes.");
}

void CylindricExtruder::generateVertices() {
    m_vertices.clear();
    // offset for reverse tris
    const Math::Vector offset(0.0, -0.01, 0.0);

    const double per = (Math::Constants::Pi*2) / m_radialCount;

    for(auto node : m_nodeList) {
        auto normal = m_nmap[node];
        Math::Vector proj(normal.x(), 0.0, normal.z());

        // ensure we're pointing in the positive-x direction.
        // this is to ensure the connections are made nicely with as little
        // rotation as possible between rings
        if(proj.x() < 0) proj = -proj;

        //Message3(Track, Debug, "tangent: " << m_tmap[node].toString());
        for(int i = 0; i < m_radialCount; i ++) {
            //Message3(Track, Debug, "Radial rotation: " <<
                    //(Math::Quaternion(m_tmap[node], per*i) * (proj*m_width)).toString());
            m_vertices.push_back(node->position() +
                Math::Quaternion(m_tmap[node], per*i) * (proj*m_width));
        }
    }
}

void CylindricExtruder::generateTris() {
    for(auto path : m_pathList) {
        for(unsigned i = 1; i < path.size(); i ++) {
            int i1 = m_nodeIndices[path[i-1]];
            int i2 = m_nodeIndices[path[i]];

            // starting vertex indices for node 1 and node 2.
            int v1 = i1*m_radialCount;
            int v2 = i2*m_radialCount;

            for(int i = 1; i <= m_radialCount; i ++) {
                // outwards facing
                m_tris.push_back(v1+i-1);
                m_tris.push_back(v1+(i%m_radialCount));
                m_tris.push_back(v2+i-1);

                m_tris.push_back(v1+(i%m_radialCount));
                m_tris.push_back(v2+(i%m_radialCount));
                m_tris.push_back(v2+i-1);
            }
        }
    }
}

void CylindricExtruder::generateNormals() {
    m_normals.clear();
    m_vertexTriCount.clear();
    for(unsigned i = 0; i < m_vertices.size(); i ++) {
        m_normals.push_back(Math::Vector());
        m_vertexTriCount.push_back(0);
    }
    for(unsigned i = 0; i < m_tris.size(); i += 3) {
        auto v1 = m_vertices[m_tris[i]];
        auto v2 = m_vertices[m_tris[i+1]];
        auto v3 = m_vertices[m_tris[i+2]];
        auto n = (v2 - v1).cross(v3 - v1).normalized();

        m_normals[m_tris[i]] += n;
        m_vertexTriCount[m_tris[i]] ++;
        m_normals[m_tris[i+1]] += n;
        m_vertexTriCount[m_tris[i+1]] ++;
        m_normals[m_tris[i+2]] += n;
        m_vertexTriCount[m_tris[i+2]] ++;
    }
    for(unsigned i = 0; i < m_normals.size(); i ++) {
        m_normals[i] /= (double)m_vertexTriCount[i];
    }
}

void CylindricExtruder::generateTexs() {
    m_texs.clear();
    for(unsigned i = 0; i < m_vertices.size(); i += 4) {
        m_texs.push_back(0.0);
        m_texs.push_back(1.0);
        m_texs.push_back(1.0);
        m_texs.push_back(0.0);
    }
}

}  // namespace Track
}  // namespace Kriti
