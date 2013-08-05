#ifndef KRITI_RENDER__RENDERBUFFER_H
#define KRITI_RENDER__RENDERBUFFER_H

namespace Kriti {
namespace Render {

class Renderbuffer {
public:
    enum Type {
        Colour,
        Depth
    };
private:
    Type m_type;
    int m_width, m_height, m_samples;
    GLuint m_id;
public:
    Renderbuffer(Type type, int width, int height, int samples = 0);
    ~Renderbuffer();

    GLuint id() const { return m_id; }
};

}  // namespace Render
}  // namespace Kriti

#endif
