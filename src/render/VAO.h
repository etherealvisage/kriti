#ifndef KRITI_RENDER__VAO_H
#define KRITI_RENDER__VAO_H

#include <vector>
#include <boost/shared_ptr.hpp>

#include "VBO.h"

namespace Kriti {
namespace Render {

class VAO {
private:
    GLuint m_arrayID;
    boost::shared_ptr<VBO> m_elementVBO;
    std::vector<boost::shared_ptr<VBO>> m_dataVBOs;
public:
    VAO();
    ~VAO();

    void addVBO(boost::shared_ptr<VBO> vbo);
    void addVBO(boost::shared_ptr<VBO> vbo, int location);

    void bind();
};

}  // namespace Render
}  // namespace Kriti

#endif
