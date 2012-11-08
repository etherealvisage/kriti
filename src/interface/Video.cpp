#include <GL/glew.h>

#include "SDL.h"

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
    SDL_Quit();
}

void Video::initializeSDL() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        Message3(Interface, Fatal, "Failed to initialize SDL: " << SDL_GetError());
    }
}

void Video::setVideoMode() {
    int width = Config::Tree::instance()->getInt("video.width", 800);
    int height = Config::Tree::instance()->getInt("video.height", 600);
    int bpp = Config::Tree::instance()->getInt("video.bpp", 24);

    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_Surface *screen = SDL_SetVideoMode(width, height, bpp, SDL_OPENGL);

    if(screen == NULL) {
        Message3(Interface, Fatal, "Failed to set video mode "
            << width << "x" << height << "x" << bpp << ": " << SDL_GetError());
    }
}

void Video::initializeGL() {
    if(glewInit() != GLEW_OK) {
        Message3(Interface, Fatal, "Failed to initialize GLEW.");
    }

    /* Basic OpenGL setup. */
    glEnable(GL_DEPTH_TEST);

    Message3(Interface, Log, "Created OpenGL context (vendor:"
        << glGetString(GL_VENDOR) << ", renderer: " << glGetString(GL_RENDERER)
        << ", version: " << glGetString(GL_VERSION)
        << ", with shading language "
        << glGetString(GL_SHADING_LANGUAGE_VERSION) << ")");

    if(!GLEW_VERSION_3_0) {
        Message3(Interface, Error, "No OpenGL 3.0 support available.");
        Message3(Interface, Fatal, "Kriti uses some OpenGL 3.0 features. "
            "Please upgrade your video drivers and try again.");
    }

    /* If video profiling is enabled . . . */
    if(Config::Tree::instance()->getBool("video.profile")) {
        if(!GLEW_ARB_timer_query) {
            Message3(Interface, Fatal, "Video profiling enabled, but "
                "GLEW_ARB_timer_query not supported.");
        }
    }
}

}  // namespace Interface
}  // namespace Kriti
