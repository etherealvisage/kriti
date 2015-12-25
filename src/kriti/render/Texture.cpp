#include <cstring>

#include <GL/glew.h>

#include <SDL_image.h>
#include <SDL_rwops.h>

#include "Texture.h"
#include "ErrorTracker.h"

#include "../ResourceRegistry.h"
#include "../XMLResource.h"
#include "../FileResource.h"
#include "../MessageSystem.h"

namespace Kriti {
namespace Render {

Texture::Texture() {
    m_type = Invalid;
    m_bindTarget = 0;
}

Texture::Texture(Type type, Target target, int width, int height, int samples)
    : m_type(type), m_target(target), m_width(width), m_height(height),
    m_samples(samples), m_id(0) {

    if(target == Simple) m_bindTarget = GL_TEXTURE_2D;
    else if(target == Cube) m_bindTarget = GL_TEXTURE_CUBE_MAP;

    makeBlank();
}

Texture::~Texture() {
    ErrorTracker::trackFrom("Texture destructor (before all)");
    glDeleteTextures(1, &m_id);
    ErrorTracker::trackFrom("Texture destructor (after delete)");
}

bool Texture::loadFrom(std::string identifier) {
    // TODO: implement support for loading cubemap textures from files.
    // TODO: implement support for loading depth textures from files.
    m_target = Simple;
    m_bindTarget = GL_TEXTURE_2D;
    m_type = Colour;
    makeTexture();

    auto node = ResourceRegistry::get<XMLResource>(
        "data")->doc().first_element_by_path(
        "/kriti/textures/").find_child_by_attribute("name",
        identifier.c_str());


    for(auto &child : node.children()) {
        if(std::strcmp(child.name(), "mipmap")) continue;

        int level = child.attribute("level").as_int(0);

        makeFromFile(std::string("textures/") + child.text().as_string(""),
            level);
    }

    return true;
}

void Texture::bindToUnit(int which) {
    ErrorTracker::trackFrom("Texture binding (before all)");
    glActiveTexture(GL_TEXTURE0 + which);
    ErrorTracker::trackFrom("Texture binding (after activate)");
    glBindTexture(GL_TEXTURE_2D, m_id);
    ErrorTracker::trackFrom("Texture binding (after bind)");
}

void Texture::reset(int width, int height, float *data) {
    m_width = width;
    m_height = height;
    GLenum iformat;
    GLenum format = GL_RGBA;
    switch(m_type) {
    case Colour:
        iformat = GL_RGBA32F;
        break;
    case ColourR:
        iformat = GL_R32F;
        format = GL_RED;
        break;
    case Depth:
        iformat = GL_DEPTH_COMPONENT32F;
        format = GL_DEPTH_COMPONENT;
        break;
    default:
        Message3(Render, Fatal, "Unknown Texture::Type in reset()");
        return;
    }

    ErrorTracker::trackFrom("Texture binding (before all)");
    glBindTexture(m_bindTarget, m_id);
    ErrorTracker::trackFrom("Texture binding (after bind)");

    glTexImage2D(GL_TEXTURE_2D,
        // level 0, no mipmapping...
        0, 
        // internal format: RGBA, floats.
        iformat,
        // width and height
        width, height,
        // border?
        0,
        // input format
        format,
        // input
        GL_FLOAT,
        // input data
        data
    );
    ErrorTracker::trackFrom("Texture binding (after image spec)");
}

void Texture::makeTexture() {
    ErrorTracker::trackFrom("Texture creation (before all)");
    glGenTextures(1, &m_id);
    ErrorTracker::trackFrom("Texture creation (after gen)");

    glBindTexture(m_bindTarget, m_id);
    ErrorTracker::trackFrom("Texture creation (after bind)");

    glTexParameteri(m_bindTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    ErrorTracker::trackFrom("Texture creation (after WRAP_S parameter)");
    glTexParameteri(m_bindTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    ErrorTracker::trackFrom("Texture creation (after WRAP_T parameter)");
    if(m_target == Cube) 
        glTexParameteri(m_bindTarget, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    ErrorTracker::trackFrom("Texture creation (after WRAP_R parameter)");
    glTexParameteri(m_bindTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    ErrorTracker::trackFrom("Texture creation (after MIN_FILTER parameter)");
    glTexParameteri(m_bindTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    ErrorTracker::trackFrom("Texture creation (after MAG_FILTER parameter)");
}

void Texture::makeBlank() {
    makeTexture();

    GLenum iformat;
    GLenum format = GL_RGBA;
    switch(m_type) {
    case Colour:
        iformat = GL_RGBA32F;
        break;
    case ColourR:
        iformat = GL_R32F;
        break;
    case Depth:
        iformat = GL_DEPTH_COMPONENT32F;
        format = GL_DEPTH_COMPONENT;
        break;
    default:
        Message3(Render, Fatal, "Unknown Texture::Type in makeBlank()");
        break;
    }
    ErrorTracker::trackFrom("Texture makeBlank (before all)");
    if(m_target == Simple) {
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
        ErrorTracker::trackFrom("Texture makeBlank (after simple image)");
    }
    else if(m_target == Cube) {
        GLuint targets[6] = {
            GL_TEXTURE_CUBE_MAP_POSITIVE_X,
            GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
            GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
            GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
            GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
            GL_TEXTURE_CUBE_MAP_NEGATIVE_Z};
        for(int i = 0; i < 6; i ++) {
            glTexImage2D(targets[i],
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
            ErrorTracker::trackFrom("Texture makeBlank (after cube image)");
        }
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    ErrorTracker::trackFrom("Texture makeBlank (after clear)");
}

void Texture::makeFromFile(std::string filename, int mipmap) {
    auto file = ResourceRegistry::get<FileResource>(filename);

    std::string contents = file->fileContent();

    SDL_Surface *result =
        IMG_Load_RW(SDL_RWFromConstMem(contents.data(), contents.size()), 1);

    if(!result) {
        Message3(Render, Error, "Could not load texture: " << IMG_GetError());
        return;
    }
    m_width = result->w;
    m_height = result->h;

    auto fmt = SDL_AllocFormat(SDL_PIXELFORMAT_ABGR8888);
    SDL_Surface *conv = SDL_ConvertSurface(result, fmt, 0);

    ErrorTracker::trackFrom("Texture makeFromFile (before all)");
    glBindTexture(GL_TEXTURE_2D, m_id);
    ErrorTracker::trackFrom("Texture makeFromFile (after bind)");

    glTexImage2D(GL_TEXTURE_2D,
        // mipmap level
        mipmap, 
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
    ErrorTracker::trackFrom("Texture makeFromFile (after image)");

    SDL_FreeSurface(result);
    SDL_FreeSurface(conv);
    SDL_FreeFormat(fmt);
}

}  // namespace Render
}  // namespace Kriti
