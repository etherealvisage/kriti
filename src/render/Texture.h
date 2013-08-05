#ifndef KRITI_RENDER__TEXTURE_H
#define KRITI_RENDER__TEXTURE_H

namespace Kriti {
namespace Render {

class Texture {
public:
    enum Type {
        ColourTexture,
        DepthTexture
    };
private:
    Type m_type;
    int m_width, m_height;
    GLuint m_id;
public:
    Texture(Type type, int width, int height);
    ~Texture();
private:
    void makeTexture();
    void makeBlank();
    void makeFromFile();
};

}  // namespace Render
}  // namespace Kriti

#endif
