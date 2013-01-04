#include <boost/make_shared.hpp>

#include <btBulletDynamicsCommon.h>

#include "DebugRenderableUpdater.h"
#include "render/RenderableFactory.h"
#include "BulletWrapper.h"

#include "Util.h"

#include "MessageSystem.h"

namespace Kriti {
namespace Physics {

DebugRenderableUpdater::DebugRenderableUpdater() {
    m_renderable = boost::make_shared<Render::Renderable>();
}

DebugRenderableUpdater::~DebugRenderableUpdater() {

}

void DebugRenderableUpdater::updateRenderable() {
    BulletWrapper::instance()->world()->debugDrawWorld();
    //if(m_renderable->renderSequenceCount() == 0) {
    //if(m_renderable->renderSequenceCount() != 0) return;
    m_renderable->clearRenderSequences();
    auto nr = Render::RenderableFactory().fromLineGeometry(m_vertices, "red");
    for(int i = 0; i < nr->renderSequenceCount(); i ++) {
        auto rs = nr->renderSequence(i);
        m_renderable->addRenderSequence(nr->renderSequence(i));
    }
    //}
    //else {
        //m_renderable->renderSequence(0)->vao()->vbo(Render::VAO::
    //}
    m_vertices.clear();
}

void DebugRenderableUpdater::drawLine(const btVector3 &from,
    const btVector3 &to, const btVector3 &color) {

    m_vertices.push_back(toMath(from));
    m_vertices.push_back(toMath(to));
}

}  // namespace Physics
}  // namespace Kriti
