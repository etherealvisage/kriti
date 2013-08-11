#include <GL/glew.h>

#include "VBO.h"

#include "MessageSystem.h"

namespace Kriti {
namespace Render {

VBO::VBO(BindType btype, UseType utype) : m_useType(utype), m_bindType(btype),
    m_bufferID(0), m_set(false) {
}

VBO::~VBO() {
    if(m_bufferID != 0) {
        glDeleteBuffers(1, &m_bufferID);
    }
}

void VBO::setData2(const std::vector<Math::Vector> &data) {
    if(!m_set) {
        m_dataType = GL_FLOAT;
        m_dataWidth = 2;
        m_set = true;
    }
    else if(m_dataType != GL_FLOAT || m_dataWidth != 2) {
        Message3(Render, Error,
            "Attempting to update VBO with different data type");
        return;
    }

    float *memory = new float[data.size()*2];
    for(unsigned i = 0; i < data.size(); i ++) {
        memory[(i*2)] = data[i].x();
        memory[(i*2)+1] = data[i].y();
    }

    makeVBO(memory, sizeof(float)*data.size()*2);

    delete[] memory;
}

void VBO::setData(const std::vector<unsigned int> &data) {
    if(!m_set) {
        m_dataType = GL_UNSIGNED_INT;
        m_dataWidth = 1;
        m_set = true;
    }
    else if(m_dataType != GL_UNSIGNED_INT || m_dataWidth != 1) {
        Message3(Render, Error,
            "Attempting to update VBO with different data type");
        return;
    }
    m_dataType = GL_UNSIGNED_INT;
    m_dataWidth = 1;

    makeVBO(&data[0], sizeof(unsigned int)*data.size());
}

void VBO::setData3(const std::vector<Math::Vector> &data) {
    if(!m_set) {
        m_dataType = GL_FLOAT;
        m_dataWidth = 3;
        m_set = true;
    }
    else if(m_dataType != GL_FLOAT || m_dataWidth != 3) {
        Message3(Render, Error,
            "Attempting to update VBO with different data type");
        return;
    }

    float *memory = new float[data.size()*3];
    for(unsigned i = 0; i < data.size(); i ++) {
        memory[(i*3)+0] = data[i].x();
        memory[(i*3)+1] = data[i].y();
        memory[(i*3)+2] = data[i].z();
    }

    makeVBO(memory, sizeof(float)*data.size()*3);

    delete[] memory;
}

void VBO::setData4(const std::vector<Math::Vector> &data, float padding) {
    if(!m_set) {
        m_dataType = GL_FLOAT;
        m_dataWidth = 4;
        m_set = true;
    }
    else if(m_dataType != GL_FLOAT || m_dataWidth != 4) {
        Message3(Render, Error,
            "Attempting to update VBO with different data type");
        return;
    }

    float *memory = new float[data.size()*4];
    for(unsigned i = 0; i < data.size(); i ++) {
        memory[(i*4)+0] = data[i].x();
        memory[(i*4)+1] = data[i].y();
        memory[(i*4)+2] = data[i].z();
        memory[(i*4)+3] = padding;
    }

    makeVBO(memory, sizeof(float)*data.size()*4);

    delete[] memory;
}

void VBO::bindVBO() {
    if(m_bindType != Element) {
        Message3(Render, Error,
            "Tried to bind non-element VBO to be element buffer.");

        return;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
}

void VBO::bindVBO(int location) {
    if(m_bindType != Data) {
        Message3(Render, Error,
            "Tried to bind non-data VBO to data location.");

        return;
    }
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
    glVertexAttribPointer(location, m_dataWidth, m_dataType, GL_FALSE, 0,
        (void *)0);
    glEnableVertexAttribArray(location);
}

void VBO::makeVBO(const void *data, int byteSize) {
    if(m_bufferID == 0) {
        glGenBuffers(1, &m_bufferID);
    }

    GLenum btype, utype;
    if(m_bindType == Data) {
        btype = GL_ARRAY_BUFFER;
    }
    else {
        btype = GL_ELEMENT_ARRAY_BUFFER;
    }

    if(m_useType == Static) {
        utype = GL_STATIC_DRAW;
    }
    else if(m_useType == Streaming) {
        utype = GL_STREAM_DRAW;
    }
    else {
        Message3(Render, Fatal, "Unknown VBO use type");
    }

    glBindBuffer(btype, m_bufferID);
    glBufferData(btype, byteSize, data, utype);
}

}  // namespace Render
}  // namespace Kriti
