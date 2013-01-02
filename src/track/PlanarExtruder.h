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
    std::vector<Math::Vector> m_vertices, m_normals;
    std::vector<unsigned int> m_tris;
public:
    PlanarExtruder(double width) : m_width(width) {}

    virtual void extrude(Node::Ptr root,
        std::vector<Math::Vector> &vertices,
        std::vector<Math::Vector> &normals,
        std::vector<unsigned int> &tris);
private:
    void findPathProperties(const std::vector<Node::Ptr> &path);
    void generateNodeList();
    void generateVertices();
    void generateTris();
    void generateNormals();
};

}  // namespace Track
}  // namespace Kriti

#endif
