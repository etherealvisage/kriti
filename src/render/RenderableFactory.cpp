#include "RenderableFactory.h"
#include "Technique.h"
#include "ResourceRegistry.h"

#include "VAO.h"
#include "VBO.h"

#include "MessageSystem.h"

namespace Kriti {
namespace Render {

boost::shared_ptr<Renderable> RenderableFactory::fromModel(
    boost::shared_ptr<Model> model) {

    boost::shared_ptr<Renderable> renderable(new Renderable());

    /* Set up VAO. */
    boost::shared_ptr<VAO> vao(new VAO());

    boost::shared_ptr<VBO> vertexVBO(new VBO());
    vertexVBO->setData(model->vertices());
    vao->addVBO(vertexVBO, 0);

    boost::shared_ptr<VBO> normalVBO(new VBO());
    normalVBO->setData(model->normals());
    vao->addVBO(normalVBO, 1);

    boost::shared_ptr<VBO> textureVBO(new VBO());
    textureVBO->setData(model->texCoords());
    vao->addVBO(textureVBO, 2);

    boost::shared_ptr<VBO> indexVBO(new VBO(true));
    indexVBO->setData(model->indices());
    vao->addVBO(indexVBO);

    /* Create RenderSequence objects. */
    for(auto ms : model->sequences()) {
        auto technique = ResourceRegistry::instance()->get<Technique>(
            ms.techniqueName());
        boost::shared_ptr<RenderSequence> rs(new RenderSequence(technique, vao,
            ms.start(), ms.end()));

        renderable->addRenderSequence(rs);
    }

    return renderable;
}

}  // namespace Render
}  // namespace Kriti
