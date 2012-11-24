#include <GL/glew.h>

#include "VBO.h"

namespace Kriti {
namespace Render {

VBO::VBO() : m_bufferID(0) {

}

void VBO::setData2(const std::vector<Math::Vector> &data) {
    m_dataType = GL_FLOAT;
    m_dataWidth = 2;

    float *memory = new float[data.size()*2];
    for(int i = 0; i < data.size()*2; i += 2) {
        memory[i] = data[i].x();
        memory[i+1] = data[i].y();
    }

    makeVBO(memory, sizeof(float)*data.size()*2);

    delete[] memory;
}

void VBO::setData(const std::vector<Math::Vector> &data) {
    m_dataType = GL_FLOAT;
    m_dataWidth = 3;

    float *memory = new float[data.size()*3];
    for(int i = 0; i < data.size()*3; i += 3) {
        memory[i] = data[i].x();
        memory[i+1] = data[i].y();
        memory[i+2] = data[i].z();
    }

    makeVBO(memory, sizeof(float)*data.size()*3);

    delete[] memory;
}

void VBO::setData(const std::vector<Math::Vector> &data, float padding) {
    m_dataType = GL_FLOAT;
    m_dataWidth = 4;

    float *memory = new float[data.size()*4];
    for(int i = 0; i < data.size()*4; i += 4) {
        memory[i] = data[i].x();
        memory[i+1] = data[i].y();
        memory[i+2] = data[i].z();
        memory[i+3] = padding;
    }

    makeVBO(memory, sizeof(float)*data.size()*4);

    delete[] memory;
}

void VBO::bindVBO(int location) {
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
    glVertexAttribPointer(location, m_dataWidth, m_dataType, GL_FALSE, 0,
        (void *)0);
    glEnableVertexAttribArray(location);
}

void VBO::makeVBO(const void *data, int byteSize) {
    if(m_bufferID == 0) {
        glGenBuffers(1, &m_bufferID);
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
    glBufferData(
        GL_ARRAY_BUFFER,
        byteSize,
        data,
        // todo: make this configurable?
        GL_STATIC_DRAW
    );
}

}  // namespace Render
}  // namespace Kriti
