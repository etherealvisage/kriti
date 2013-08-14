#include <GL/glew.h>

#include <SDL_image.h>
#include <SDL_rwops.h>

#include "Texture.h"

#include "ResourceRegistry.h"
#include "FileResource.h"
#include "MessageSystem.h"

namespace Kriti {
namespace Render {

Texture::Texture() {
    makeTexture();
}

Texture::Texture(Type type, int width, int height, int samples) : m_type(type),
    m_width(width), m_height(height), m_samples(samples) {

    makeBlank();
}

Texture::~Texture() {
    glDeleteTextures(1, &m_id);
}

bool Texture::loadFrom(std::string identifier) {
    auto file = ResourceRegistry::get<FileResource>(
        "textures/" + identifier + ".png");

    std::string contents = file->fileContent();

    SDL_Surface *result =
        IMG_Load_RW(SDL_RWFromConstMem(contents.data(), contents.size()), 1);

    if(!result) {
        Message3(Render, Error, "Could not load texture: " << IMG_GetError());
        return false;
    }
    m_width = result->w;
    m_height = result->h;

    //auto fmt = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    auto fmt = SDL_AllocFormat(SDL_PIXELFORMAT_ABGR8888);
    SDL_Surface *conv = SDL_ConvertSurface(result, fmt, 0);

    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexImage2D(GL_TEXTURE_2D,
        // level 0, no mipmapping...
        0, 
        // internal format: RGBA, floats.
        GL_RGBA32F,
        // width and height
        m_width, m_height,
        // border?
        0,
        // input format
        GL_RGBA,
        // input
        GL_UNSIGNED_BYTE,
        // input data
        conv->pixels
    );

    SDL_FreeSurface(result);
    SDL_FreeSurface(conv);
    SDL_FreeFormat(fmt);

    return true;
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
