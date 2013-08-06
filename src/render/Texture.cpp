#include <GL/glew.h>

#include "Texture.h"

#include "MessageSystem.h"

namespace Kriti {
namespace Render {

Texture::Texture(Type type, int width, int height) : m_type(type),
    m_width(width), m_height(height) {

    makeBlank();
}

Texture::~Texture() {
    glDeleteTextures(1, &m_id);
}

void Texture::bindToUnit(int which) {
    glActiveTexture(GL_TEXTURE0 + which);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::makeTexture() {
    glGenTextures(1, &m_id);

    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::makeBlank() {
    makeTexture();

    GLenum iformat;
    GLenum format = GL_RGBA;
    switch(m_type) {
    case Colour:
        iformat = GL_RGBA32F;
        break;
    case Depth:
        iformat = GL_DEPTH_COMPONENT32F;
        break;
    default:
        Message3(Render, Fatal, "Unknown Texture::Type in makeBlank()");
        break;
    }
    glTexImage2D(GL_TEXTURE_2D,
        // level 0, no mipmapping...
        0, 
        // internal format: RGBA, floats.
        iformat,
        // width and height
        m_width, m_height,
        // border?
        0,
        // input format
        format,
        // input
        GL_UNSIGNED_BYTE,
        // input data
        nullptr
    );

    glBindTexture(GL_TEXTURE_2D, 0);
}

}  // namespace Render
}  // namespace Kriti
