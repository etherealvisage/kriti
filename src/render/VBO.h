#ifndef KRITI_RENDER__VBO_H
#define KRITI_RENDER__VBO_H

#include <vector>

#include "math/Vector.h"

namespace Kriti {
namespace Render {

class VBO {
public:
    enum UseType {
        Static,
        Streaming
    };
    enum BindType {
        Data,
        Element
    };
private:
    UseType m_useType;
    BindType m_bindType;
    GLuint m_bufferID;
    GLenum m_dataType;
    GLint m_dataWidth;
public:
    explicit VBO(BindType btype = Data, UseType utype = Static);
    ~VBO();

    void setData2(const std::vector<Math::Vector> &data);
    void setData(const std::vector<unsigned int> &data);
    void setData(const std::vector<Math::Vector> &data);
    void setData(const std::vector<Math::Vector> &data, float padding);

    void bindVBO();
    void bindVBO(int location);
private:
    void makeVBO(const void *data, int byteSize);
};

}  // namespace Render
}  // namespace Kriti

#endif
