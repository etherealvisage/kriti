#include <cstring>

#include "../ogl.h"

#include <SDL_image.h>
#include <SDL_rwops.h>

#include "Texture.h"
#include "TextureContext.h"
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

    m_width = m_height = m_samples = 0;
}

Texture::Texture(Type type, Target target, int width, int height, int samples)
    : m_type(type), m_target(target), m_width(width), m_height(height),
    m_samples(samples), m_id(0) {

    if(target == Simple) {
        if(samples == 0) m_bindTarget = gl::TEXTURE_2D;
        else m_bindTarget = gl::TEXTURE_2D_MULTISAMPLE;
    }
    else if(target == Cube) m_bindTarget = gl::TEXTURE_CUBE_MAP;

    makeBlank();
}

Texture::~Texture() {
    ErrorTracker::trackFrom("Texture destructor (before all)");
    gl::DeleteTextures(1, &m_id);
    ErrorTracker::trackFrom("Texture destructor (after delete)");
}

bool Texture::loadFrom(std::string identifier) {
    // TODO: implement support for loading cubemap textures from files.
    // TODO: implement support for loading depth textures from files.
    m_target = Simple;
    m_bindTarget = gl::TEXTURE_2D;
    m_type = Colour;
    m_samples = 0;
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
    gl::ActiveTexture(gl::TEXTURE0 + which);
    ErrorTracker::trackFrom("Texture binding (after activate)");
    gl::BindTexture(m_bindTarget, m_id);
    ErrorTracker::trackFrom("Texture binding (after bind)");
}

void Texture::reset(int width, int height, float *data) {
    m_width = width;
    m_height = height;
    GLenum iformat;
    GLenum format = gl::RGBA;
    switch(m_type) {
    case Colour:
        iformat = gl::RGBA32F;
        break;
    case ColourR:
        iformat = gl::R32F;
        format = gl::RED;
        break;
    case Depth:
        iformat = gl::DEPTH_COMPONENT32F;
        format = gl::DEPTH_COMPONENT;
        break;
    default:
        Message3(Render, Fatal, "Unknown Texture::Type in reset()");
        return;
    }

    ErrorTracker::trackFrom("Texture binding (before all)");
    gl::BindTexture(m_bindTarget, m_id);
    ErrorTracker::trackFrom("Texture binding (after bind)");

    gl::TexImage2D(gl::TEXTURE_2D,
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
        gl::FLOAT,
        // input data
        data
    );
    ErrorTracker::trackFrom("Texture binding (after image spec)");
}

void Texture::makeTexture() {
    ErrorTracker::trackFrom("Texture creation (before all)");
    gl::GenTextures(1, &m_id);
    ErrorTracker::trackFrom("Texture creation (after gen)");

    // XXX: for now, just clear all texture bindings
    // In the future, clear only the current texture binding
    TextureContext::instance()->clearBindings();

    gl::BindTexture(m_bindTarget, m_id);
    ErrorTracker::trackFrom("Texture creation (after bind)");

    if(m_samples == 0) {
        gl::TexParameteri(m_bindTarget, gl::TEXTURE_WRAP_S, gl::CLAMP_TO_EDGE);
        ErrorTracker::trackFrom("Texture creation (after WRAP_S parameter)");
        gl::TexParameteri(m_bindTarget, gl::TEXTURE_WRAP_T, gl::CLAMP_TO_EDGE);
        ErrorTracker::trackFrom("Texture creation (after WRAP_T parameter)");
        if(m_target == Cube)
            gl::TexParameteri(m_bindTarget, gl::TEXTURE_WRAP_R,
                gl::CLAMP_TO_EDGE);
        ErrorTracker::trackFrom("Texture creation (after WRAP_R parameter)");
        gl::TexParameteri(m_bindTarget, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
        ErrorTracker::trackFrom(
            "Texture creation (after MIN_FILTER parameter)");
        gl::TexParameteri(m_bindTarget, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
        ErrorTracker::trackFrom(
            "Texture creation (after MAG_FILTER parameter)");
    }
}

void Texture::makeBlank() {
    makeTexture();

    GLenum iformat;
    GLenum format = gl::RGBA;
    switch(m_type) {
    case Colour:
        iformat = gl::RGBA32F;
        break;
    case ColourR:
        iformat = gl::R32F;
        break;
    case Depth:
        iformat = gl::DEPTH_COMPONENT32F;
        format = gl::DEPTH_COMPONENT;
        break;
    default:
        Message3(Render, Fatal, "Unknown Texture::Type in makeBlank()");
        break;
    }
    ErrorTracker::trackFrom("Texture makeBlank (before all)");
    if(m_target == Simple) {
        if(m_samples == 0) {
            gl::TexImage2D(gl::TEXTURE_2D,
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
                gl::UNSIGNED_BYTE,
                // input data
                nullptr
            );
            ErrorTracker::trackFrom("Texture makeBlank (after simple image)");
        }
        else {
            gl::TexImage2DMultisample(gl::TEXTURE_2D_MULTISAMPLE,
                m_samples,
                iformat,
                // width and height
                m_width, m_height,
                gl::TRUE_);
        }
    }
    else if(m_target == Cube) {
        GLuint targets[6] = {
            gl::TEXTURE_CUBE_MAP_POSITIVE_X,
            gl::TEXTURE_CUBE_MAP_POSITIVE_Y,
            gl::TEXTURE_CUBE_MAP_POSITIVE_Z,
            gl::TEXTURE_CUBE_MAP_NEGATIVE_X,
            gl::TEXTURE_CUBE_MAP_NEGATIVE_Y,
            gl::TEXTURE_CUBE_MAP_NEGATIVE_Z};
        for(int i = 0; i < 6; i ++) {
            gl::TexImage2D(targets[i],
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
                gl::UNSIGNED_BYTE,
                // input data
                nullptr
            );
            ErrorTracker::trackFrom("Texture makeBlank (after cube image)");
        }
    }

    if(m_samples == 0) {
        gl::BindTexture(gl::TEXTURE_2D, 0);
    }
    else {
        gl::BindTexture(gl::TEXTURE_2D_MULTISAMPLE, 0);
    }
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
    gl::BindTexture(gl::TEXTURE_2D, m_id);
    ErrorTracker::trackFrom("Texture makeFromFile (after bind)");

    gl::TexImage2D(gl::TEXTURE_2D,
        // mipmap level
        mipmap, 
        // internal format: RGBA, floats.
        gl::RGBA32F,
        // width and height
        m_width, m_height,
        // border?
        0,
        // input format
        gl::RGBA,
        // input
        gl::UNSIGNED_BYTE,
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
