#ifndef KRITI_TRACK__PLANAR_EXTRUDER_H
#define KRITI_TRACK__PLANAR_EXTRUDER_H

#include <map>

#include "Extruder.h"

namespace Kriti {
namespace Track {

class PlanarExtruder : public Extruder {
private:
    double m_width;
    Node::Ptr m_root;
    std::vector<std::vector<Node::Ptr>> m_pathList;
    std::map<Node::Ptr, Math::Vector> m_tmap, m_nmap;
    std::vector<Node::Ptr> m_nodeList;
    std::map<Node::Ptr, int> m_nodeIndices;
    std::vector<Math::Vector> m_vertices, m_normals, m_texs;
    std::vector<int> m_vertexTriCount;
    std::vector<unsigned int> m_tris;
public:
    PlanarExtruder(double width) : m_width(width) {}

    virtual boost::shared_ptr<ExtrusionResult> extrude(Node::Ptr root);
private:
    void findPathProperties(const std::vector<Node::Ptr> &path);
    void generateNodeList();
    void generateVertices();
    void generateTris();
    void generateNormals();
    void generateTexs();
};

}  // namespace Track
}  // namespace Kriti

#endif
