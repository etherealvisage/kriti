#ifndef KRITI_INTERFACE__VIDEO_H
#define KRITI_INTERFACE__VIDEO_H

#include <boost/shared_ptr.hpp>

#include <SDL.h>

namespace Kriti {
namespace Interface {

class Video {
private:
    static boost::shared_ptr<Video> s_singleton;
public:
    static boost::shared_ptr<Video> instance() {
        if(!s_singleton) {
            s_singleton = boost::shared_ptr<Video>(new Video());
        }
        return s_singleton;
    }
    static void destroy() {
        s_singleton.reset();
    }
private:
    SDL_Window *m_window;
    SDL_GLContext m_context;
private:
    Video();
public:
    ~Video();

    double aspectRatio() const;

    void swapBuffers();
private:
    void initializeSDL();
    void setVideoMode();
    void initializeGL();
};

}  // namespace Interface
}  // namespace Kriti

#endif
