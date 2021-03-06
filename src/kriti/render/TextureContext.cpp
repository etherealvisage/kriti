#include "../ogl.h"

#include "TextureContext.h"
#include "Texture.h"
#include "ErrorTracker.h"

#include "../MessageSystem.h"

namespace Kriti {
namespace Render {

TextureContext::TextureContext() {
    ErrorTracker::trackFrom("Texture context constructor (before all)");
    GLint count;
    gl::GetIntegerv(gl::MAX_COMBINED_TEXTURE_IMAGE_UNITS, &count);
    ErrorTracker::trackFrom(
        "Texture context constructor (after get unit count)");

    m_bindings.assign(count, std::make_pair(-1, boost::shared_ptr<Texture>()));

    m_round = 0;
    m_lastUnit = -1;
}

void TextureContext::clearBindings() {
    m_lastUnit = -1;
    m_bindings.assign(m_bindings.size(),
        std::make_pair(-1, boost::shared_ptr<Texture>()));
}

int TextureContext::bind(boost::shared_ptr<Texture> texture) {
    // first check if it's already bound...
    for(int i = 0; i < m_bindings.size(); i ++) {
        if(m_bindings[i].second == texture) {
            m_bindings[i].first = m_round;
            return i;
        }
    }

    // find next available to bind on
    for(int i = 1; i < m_bindings.size(); i ++) {
        int in = (m_lastUnit+i)%m_bindings.size();
        if(m_bindings[in].first >= m_round) continue;

        //Message3(Render, Debug, "Selecting texture unit offset " << i);

        m_bindings[in] = std::make_pair(m_round, texture);

        texture->bindToUnit(in);
        m_lastUnit = in;

        //Message3(Render, Debug, "Seting last unit to " << m_lastUnit);
        return in;
    }

    Message3(Render, Error, "Exhausted the supply of texture units!");
    // in this case -- which shouldn't happen -- just use texture 0.
    return 0;
}

}  // namespace Render
}  // namespace Kriti
