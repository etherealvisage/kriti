#ifndef KRITI_RENDER__TEXTURE_H
#define KRITI_RENDER__TEXTURE_H

#include <GL/gl.h>

#include "../Resource.h"

namespace Kriti {
namespace Render {

class Texture : public Resource {
public:
    enum Type {
        Colour,
        ColourR,
        Depth,
        Invalid
    };
    enum Target {
        Simple, // 2D texture
        Cube
    };
private:
    Type m_type;
    Target m_target;
    int m_width, m_height;
    int m_samples;
    GLuint m_id;
    GLuint m_bindTarget;
public:
    Texture();
    Texture(Type type, Target target, int width, int height, int samples=0);
    ~Texture();

    GLuint id() const { return m_id; }

    int width() const { return m_width; }
    int height() const { return m_height; }

    virtual bool loadFrom(std::string identifier);

    void bindToUnit(int which);

    void reset(int width, int height, float *data);
private:
    void makeTexture();
    void makeBlank();
    void makeFromFile(std::string filename, int mipmap);
};

}  // namespace Render
}  // namespace Kriti

#endif
