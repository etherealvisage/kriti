#ifndef KRITI_RENDER__TEXTURE_CONTEXT_H
#define KRITI_RENDER__TEXTURE_CONTEXT_H

#include <vector>

#include <stdint.h>

#include <boost/shared_ptr.hpp>

namespace Kriti {
namespace Render {

class Texture;

class TextureContext {
private:
    static boost::shared_ptr<TextureContext> s_singleton;
public:
    static boost::shared_ptr<TextureContext> instance() {
        if(!s_singleton) {
            s_singleton = boost::shared_ptr<TextureContext>(
                new TextureContext());
        }
        return s_singleton;
    }
    static void destroy() {
        s_singleton.reset();
    }
private:
    int64_t m_round;
    std::vector<std::pair<int64_t, boost::shared_ptr<Texture>>> m_bindings;
    int m_lastUnit;
private:
    TextureContext();
public:
    void nextProgram() { m_round ++; }
    void clearBindings();

    int bind(boost::shared_ptr<Texture> texture);
};

}  // namespace Render
}  // namespace Kriti

#endif
