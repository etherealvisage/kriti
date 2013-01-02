#ifndef KRITI_TRACK__EXTRUSION_RESULT_H
#define KRITI_TRACK__EXTRUSION_RESULT_H

#include <vector>

#include "math/Vector.h"

namespace Kriti {
namespace Track {

class ExtrusionResult {
private:
    std::vector<Math::Vector> m_vertices, m_normals, m_texs;
    std::vector<unsigned int> m_indices;
public:
    // Note: this destroys the input vector contents.
    ExtrusionResult(std::vector<Math::Vector> &vertices,
        std::vector<Math::Vector> &normals,
        std::vector<Math::Vector> &texs,
        std::vector<unsigned int> &indices) {

        m_vertices.swap(vertices);
        m_normals.swap(normals);
        m_texs.swap(texs);
        m_indices.swap(indices);
    }

    const std::vector<Math::Vector> &vertices() const { return m_vertices; }
    const std::vector<Math::Vector> &normals() const { return m_normals; }
    const std::vector<Math::Vector> &texs() const { return m_texs; }
    const std::vector<unsigned int> &indices() const { return m_indices; }
};

}  // namespace Track
}  // namespace Kriti

#endif
