#ifndef KRITI_RENDER__VBO_H
#define KRITI_RENDER__VBO_H

#include <vector>

#include "math/Vector.h"

namespace Kriti {
namespace Render {

class VBO {
private:
    GLuint m_bufferID;
    GLenum m_dataType;
    GLint m_dataWidth;
public:
    VBO();

    void setData2(const std::vector<Math::Vector> &data);
    void setData(const std::vector<Math::Vector> &data);
    void setData(const std::vector<Math::Vector> &data, float padding);

    void bindVBO(int location);
private:
    void makeVBO(const void *data, int byteSize);
};

}  // namespace Render
}  // namespace Kriti

#endif
