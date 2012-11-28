#include <GL/glew.h>

#include "VBO.h"

#include "MessageSystem.h"

namespace Kriti {
namespace Render {

VBO::VBO(bool isElementData) : m_bufferID(0) {
    if(isElementData) {
        m_bindType = GL_ELEMENT_ARRAY_BUFFER;
    }
    else {
        m_bindType = GL_ARRAY_BUFFER;
    }
}

VBO::~VBO() {
    if(m_bufferID != 0) {
        glDeleteBuffers(1, &m_bufferID);
    }
}

void VBO::setData2(const std::vector<Math::Vector> &data) {
    m_dataType = GL_FLOAT;
    m_dataWidth = 2;

    float *memory = new float[data.size()*2];
    for(unsigned i = 0; i < data.size()*2; i += 2) {
        memory[i] = data[i].x();
        memory[i+1] = data[i].y();
    }

    makeVBO(memory, sizeof(float)*data.size()*2);

    delete[] memory;
}

void VBO::setData(const std::vector<unsigned int> &data) {
    m_dataType = GL_UNSIGNED_INT;
    m_dataWidth = 1;

    makeVBO(&data[0], sizeof(unsigned int)*data.size());
}

void VBO::setData(const std::vector<Math::Vector> &data) {
    m_dataType = GL_FLOAT;
    m_dataWidth = 3;

    float *memory = new float[data.size()*3];
    for(unsigned i = 0; i < data.size(); i ++) {
        memory[(i*3)] = data[i].x();
        memory[(i*3)+1] = data[i].y();
        memory[(i*3)+2] = data[i].z();
    }

    makeVBO(memory, sizeof(float)*data.size()*3);

    delete[] memory;
}

void VBO::setData(const std::vector<Math::Vector> &data, float padding) {
    m_dataType = GL_FLOAT;
    m_dataWidth = 4;

    float *memory = new float[data.size()*4];
    for(unsigned i = 0; i < data.size()*4; i += 4) {
        memory[i] = data[i].x();
        memory[i+1] = data[i].y();
        memory[i+2] = data[i].z();
        memory[i+3] = padding;
    }

    makeVBO(memory, sizeof(float)*data.size()*4);

    delete[] memory;
}

void VBO::bindVBO() {
    if(m_bindType != GL_ELEMENT_ARRAY_BUFFER) {
        Message3(Render, Error,
            "Tried to bind data VBO to be element buffer.");

        return;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
}

void VBO::bindVBO(int location) {
    if(m_bindType != GL_ARRAY_BUFFER) {
        Message3(Render, Error,
            "Tried to bind element data VBO to data location.");

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

    glBindBuffer(m_bindType, m_bufferID);
    glBufferData(m_bindType, byteSize, data, GL_STATIC_DRAW);
}

}  // namespace Render
}  // namespace Kriti
