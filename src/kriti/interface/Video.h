#ifndef KRITI_INTERFACE__VIDEO_H
#define KRITI_INTERFACE__VIDEO_H

#include <boost/shared_ptr.hpp>

#include <SDL.h>

#include "../Globals.h"

namespace Kriti {
namespace Interface {

class Video { KRITI_GLOBAL(Video)
private:
    SDL_Window *m_window;
    SDL_GLContext m_context;
    int m_width, m_height;
    bool m_msaa;
    int m_aasamples;
private:
    Video();
public:
    ~Video();

    int width() const { return m_width; }
    int height() const { return m_height; }
    double aspectRatio() const;

    bool msaa() const { return m_msaa; }
    int aasamples() const { return m_aasamples; }

    void swapBuffers();
private:
    void initializeSDL();
    void setVideoMode();
    void initializeGL();
};

}  // namespace Interface
}  // namespace Kriti

#endif
