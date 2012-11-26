#ifndef KRITI_RENDER__MODEL_H
#define KRITI_RENDER__MODEL_H

#include <tuple>
#include <map>
#include <vector>

#include "Resource.h"

#include "ModelSequence.h"

#include "math/Vector.h"

namespace Kriti {
namespace Render {

class Model : public Resource {
private:
    std::vector<Math::Vector> m_vertices;
    std::vector<Math::Vector> m_normals;
    std::vector<Math::Vector> m_texCoords;
    std::vector<int> m_indices;
    std::vector<ModelSequence> m_sequences;

    /* used for construction purposes. */
    std::vector<Math::Vector> m_objVertices;
    std::vector<Math::Vector> m_objNormals;
    std::vector<Math::Vector> m_objTexCoords;
    std::map<std::tuple<int, int, int>, int> m_objIndices;
public:
    const std::vector<Math::Vector> &vertices() const
        { return m_vertices; }
    const std::vector<Math::Vector> &normals() const
        { return m_normals; }
    const std::vector<Math::Vector> &texCoords() const
        { return m_texCoords; }
    const std::vector<int> &indices() const
        { return m_indices; }
    const std::vector<ModelSequence> &sequences() const
        { return m_sequences; }

    virtual bool loadFrom(std::string identifier);
private:
    void addFaceEntry(int vi, int ti, int ni);
};

}  // namespace Render
}  // namespace Kriti

#endif
