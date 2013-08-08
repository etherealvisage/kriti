#ifndef KRITI_RENDER__TEXTURE_H
#define KRITI_RENDER__TEXTURE_H

#include "Resource.h"

namespace Kriti {
namespace Render {

class Texture : public Resource {
public:
    enum Type {
        Colour,
        Depth
    };
private:
    Type m_type;
    int m_width, m_height;
    int m_samples;
    GLuint m_id;
public:
    Texture();
    Texture(Type type, int width, int height, int samples=0);
    ~Texture();

    GLuint id() const { return m_id; }

    int width() const { return m_width; }
    int height() const { return m_height; }

    virtual bool loadFrom(std::string identifier);

    void bindToUnit(int which);
private:
    void makeTexture();
    void makeBlank();
    void makeFromFile();
};

}  // namespace Render
}  // namespace Kriti

#endif
