#ifndef KRITI_RENDER__RENDER_SEQUENCE_H
#define KRITI_RENDER__RENDER_SEQUENCE_H

#include "Technique.h"
#include "VAO.h"

namespace Kriti {
namespace Render {

class RenderSequence {
private:
    Technique *m_technique;
    std::vector<int> m_elements;
    GLuint m_elementBufferID;
    VAO *m_meshVAO;
public:
    void setTechnique(Technique *technique) { m_technique = technique; }
    void setElementList(std::vector<int> elements);
    void setVAO(VAO *vao) { m_meshVAO = vao; }

    void draw();
private:
    void generateBuffer();
};

}  // namespace Render
}  // namespace Kriti

#endif
