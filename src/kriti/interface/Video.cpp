#include "../ogl.h"

#include <SDL.h>
#include <SDL_video.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include "Video.h"

#include "../MessageSystem.h"
#include "../ResourceRegistry.h"
#include "../XMLResource.h"

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

    SDL_ShowCursor(0);
}

void Video::setVideoMode() {
    const pugi::xml_node &videoconfig =
        ResourceRegistry::get<XMLResource>(
        "config")->doc().first_element_by_path("/kriti/video");

    m_width = videoconfig.first_element_by_path("resolution").attribute(
        "width").as_int(800);
    m_height = videoconfig.first_element_by_path("resolution").attribute(
        "height").as_int(600);
    int bpp = videoconfig.first_element_by_path("resolution").attribute(
        "bpp").as_int(0);
    bool fullscreen = videoconfig.first_element_by_path(
        "/fullscreen").text().as_bool(false);

    m_msaa = false;
    m_aasamples = 1;
    auto aa_node = videoconfig.first_element_by_path("msaa");
    if(aa_node) {
        m_msaa = aa_node.attribute("enabled").as_bool(false);
        m_aasamples = aa_node.attribute("samples").as_int(4);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    // Want a core profile instead of a compatability context.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
        SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    if(m_msaa) {
        int ret = SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        if(ret != 0) {
            Message3(Interface, Fatal,
                "Failed to set MULTISAMPLEBUFFERS to 1");
        }
        ret = SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, m_aasamples);
        if(ret != 0) {
            Message3(Interface, Fatal,
                "Failed to set MULTISAMPLESAMPLES to " << m_aasamples);
        }
    }

    int flags = SDL_WINDOW_OPENGL;
    if(fullscreen) flags |= SDL_WINDOW_FULLSCREEN;
    m_window = SDL_CreateWindow("kriti",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        m_width, m_height, flags);

    if(m_window == NULL) {
        Message3(Interface, Fatal, "Failed to set video mode "
            << m_width << "x" << m_height << "x" << bpp << ": "
            << SDL_GetError());
    }

    m_context = SDL_GL_CreateContext(m_window);
}

void Video::initializeGL() {
    gl::exts::LoadTest loaded = gl::sys::LoadFunctions();
    if(!loaded) {
        Message3(Interface, Error, "No OpenGL 3.1 support available.");
        Message3(Interface, Fatal, "Kriti uses some OpenGL 3.1 features. "
            "Please upgrade your video drivers and try again.");
    }

    int nfailed = loaded.GetNumMissing();
    if(nfailed != 0) {
        Message3(Interface, Error, "Failed to load " << nfailed
            << " GL function(s).");
    }

    /* Basic OpenGL setup. */
    gl::Enable(gl::DEPTH_TEST);
    gl::DepthFunc(gl::LESS);

    gl::FrontFace(gl::CCW);
    //glEnable(GL_CULL_FACE);

    gl::Enable(gl::BLEND);
    gl::BlendFuncSeparate(gl::SRC_ALPHA, gl::ONE_MINUS_SRC_ALPHA,
        gl::SRC_ALPHA, gl::DST_ALPHA);
    gl::BlendEquationSeparate(gl::FUNC_ADD, gl::MAX);

    gl::ClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    Message3(Interface, Log, "Created OpenGL context (vendor:"
        << gl::GetString(gl::VENDOR) << ", renderer: "
        << gl::GetString(gl::RENDERER)
        << ", version: " << gl::GetString(gl::VERSION)
        << ", with shading language "
        << gl::GetString(gl::SHADING_LANGUAGE_VERSION) << ")");

    /* If video profiling is enabled . . . */
    if(ResourceRegistry::get<XMLResource>(
        "config")->doc().first_element_by_path(
        "/kriti/general/profile").text().as_bool(false)
        && !gl::exts::var_ARB_timer_query) {

        Message3(Interface, Fatal, "Profiling enabled, but "
            "GL_ARB_timer_query extension not present.");
    }

    if(m_msaa) {
        if(!gl::exts::var_ARB_texture_multisample) {
            Message3(Interface, Fatal,
                "MSAA enabled but var_ARB_texture_multisample not present!");
        }
        else {
            gl::Enable(gl::MULTISAMPLE);
        }
    }

    /* Need GL_ARB_explicit_attrib_location for shaders; it's in GL 3.3.*/
    if(!gl::exts::var_ARB_explicit_attrib_location) {
        Message3(Interface, Fatal,
            "GL_ARB_explicit_attrib_location OpenGL extension required.");
    }
    /* Need GL_ARB_viewport_array for point light sources. */
    if(!gl::exts::var_ARB_viewport_array) {
        Message3(Interface, Fatal,
            "GL_ARB_viewport_array OpenGL extension required.");
    }
}

}  // namespace Interface
}  // namespace Kriti
