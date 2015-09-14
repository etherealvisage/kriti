#ifndef KRITI_RENDER__VAO_H
#define KRITI_RENDER__VAO_H

#include <vector>
#include <boost/shared_ptr.hpp>

#include "VBO.h"

namespace Kriti {
namespace Render {

class VAO {
public:
    enum Location {
        Vertex, // 0
        Normal, // 1
        Colour0, // 2
        Colour1, // 3
        Colour2, // 4
        Colour3, // 5
        Texture0, // 6
        Texture1, // 7
        Texture2, // 8
        Texture3, // 9
        Element,
        Locations
    };
private:
    GLuint m_arrayID;
    boost::shared_ptr<VBO> m_vbos[Locations];
public:
    VAO();
    ~VAO();

    void addVBO(boost::shared_ptr<VBO> vbo, Location where);
    boost::shared_ptr<VBO> vbo(int location) const
        { return m_vbos[location]; }

    void bind();
};

}  // namespace Render
}  // namespace Kriti

#endif
