#ifndef KRITI_RENDER__VAO_H
#define KRITI_RENDER__VAO_H

#include "Mesh.h"

namespace Kriti {
namespace Render {

class VAO {
private:
    GLuint m_arrayID;
    Mesh *m_mesh;
public:
    VAO();

    void wrap(Mesh *mesh);
    void bind();
};

}  // namespace Render
}  // namespace Kriti

#endif
