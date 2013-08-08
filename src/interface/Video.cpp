#include <GL/glew.h>

#include <SDL.h>
#include <SDL_video.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include "Video.h"
#include "config/Tree.h"
#include "MessageSystem.h"

namespace Kriti {
namespace Interface {

boost::shared_ptr<Video> Video::s_singleton;

Video::Video() {
    initializeSDL();
    setVideoMode();
    initializeGL();
}

Video::~Video() {
    IMG_Quit();
    SDL_Quit();
}

double Video::aspectRatio() const {
    return (double)m_width/m_height;
}

void Video::swapBuffers() {
    SDL_GL_SwapWindow(m_window);
}

void Video::initializeSDL() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        Message3(Interface, Fatal, "Failed to initialize SDL: "
            << SDL_GetError());
    }

    if(IMG_Init(IMG_INIT_PNG) < 0) {
        Message3(Interface, Fatal, "Failed to initialize SDL_image: "
            << IMG_GetError());
    }
}

void Video::setVideoMode() {
    m_width = Config::Tree::instance()->getInt("video.width", 800);
    m_height = Config::Tree::instance()->getInt("video.height", 600);
    int bpp = Config::Tree::instance()->getInt("video.bpp", 24);
    bool fullscreen = Config::Tree::instance()->getBool("video.fullscreen",
        false);

    // Need OpenGL 3.1 (well, GLSL 1.40) for easy
    // GL_ARB_explicit_attrib_location support in shaders on NVidia GPUs.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    int flags = SDL_WINDOW_OPENGL;
    if(fullscreen) flags |= SDL_WINDOW_FULLSCREEN;
    m_window = SDL_CreateWindow("kriti",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        m_width, m_height, flags);

    if(m_window == NULL) {
        Message3(Interface, Fatal, "Failed to set video mode "
            << m_width << "x" << m_height << "x" << bpp << ": " << SDL_GetError());
    }

    m_context = SDL_GL_CreateContext(m_window);
}

void Video::initializeGL() {
    GLenum status = glewInit();
    if(status != GLEW_OK) {
        Message3(Interface, Fatal, "Failed to initialize GLEW: "
            << glewGetErrorString(status));
    }

    /* Basic OpenGL setup. */
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glFrontFace(GL_CCW);
    //glEnable(GL_CULL_FACE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    Message3(Interface, Log, "Created OpenGL context (vendor:"
        << glGetString(GL_VENDOR) << ", renderer: " << glGetString(GL_RENDERER)
        << ", version: " << glGetString(GL_VERSION)
        << ", with shading language "
        << glGetString(GL_SHADING_LANGUAGE_VERSION) << ")");

    if(!GLEW_VERSION_3_1) {
        Message3(Interface, Error, "No OpenGL 3.1 support available.");
        Message3(Interface, Fatal, "Kriti uses some OpenGL 3.1 features. "
            "Please upgrade your video drivers and try again.");
    }

    /* If video profiling is enabled . . . */
    if(Config::Tree::instance()->getBool("kriti.profile")) {
        if(!GLEW_ARB_timer_query) {
            Message3(Interface, Fatal, "Profiling enabled, but "
                "GLEW_ARB_timer_query GL extension not supported.");
        }
    }
    if(!GL_ARB_explicit_attrib_location) {
        Message3(Interface, Fatal,
            "GL_ARB_explicit_attrib_location OpenGL extension required.");
    }

    GLint maxColourAttachments;
    glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &maxColourAttachments);
    Message3(Interface, Log, "Maximum number of colour attachments: " << maxColourAttachments);

    GLint maxSamples;
    glGetIntegerv(GL_MAX_SAMPLES, &maxSamples);
    Message3(Interface, Log, "Maximum number of samples: " << maxSamples);
}

}  // namespace Interface
}  // namespace Kriti
