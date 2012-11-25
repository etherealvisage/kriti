#ifndef KRITI_RENDER__MODEL_H
#define KRITI_RENDER__MODEL_H

#include <tuple>
#include <map>
#include <vector>

#include "Resource.h"

#include "math/Vector.h"

namespace Kriti {
namespace Render {

class Model : public Resource {
private:
    std::vector<Math::Vector> m_vertices;
    std::vector<Math::Vector> m_normals;
    std::vector<Math::Vector> m_texCoords;
    std::vector<int> m_indices;

    /* used for construction purposes. */
    std::vector<Math::Vector> m_objVertices;
    std::vector<Math::Vector> m_objNormals;
    std::vector<Math::Vector> m_objTexCoords;
    std::map<std::tuple<int, int, int>, int> m_objIndices;
public:
    virtual bool loadFrom(std::string identifier);
private:
    void addFaceEntry(int vi, int ti, int ni);
};

}  // namespace Render
}  // namespace Kriti

#endif
