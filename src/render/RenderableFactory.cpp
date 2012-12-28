#include <boost/make_shared.hpp>

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

boost::shared_ptr<Renderable> RenderableFactory::fromTriangleGeometry(
    const std::vector<Math::Vector> &geometry, std::string technique) {
    
    auto renderable = boost::make_shared<Renderable>();
    auto vao = boost::make_shared<VAO>();

    auto vertexVBO = boost::make_shared<VBO>();
    vertexVBO->setData(geometry);
    vao->addVBO(vertexVBO, 0);

    std::vector<Math::Vector> normals;
    for(unsigned i = 0; i < geometry.size(); i += 3) {
        auto normal = (geometry[i+2] - geometry[i]).cross(
            geometry[i+1] - geometry[i]).normalized();
        normals.push_back(normal);
        normals.push_back(normal);
        normals.push_back(normal);
    }

    auto normalVBO = boost::make_shared<VBO>();
    normalVBO->setData(normals);
    vao->addVBO(normalVBO, 1);

    auto textureVBO = boost::make_shared<VBO>();
    std::vector<Math::Vector> texs;
    for(unsigned i = 0; i < geometry.size(); i ++) {
        texs.push_back(Math::Vector());
    }
    textureVBO->setData(texs);
    vao->addVBO(textureVBO, 2);

    std::vector<unsigned int> indices;
    for(unsigned i = 0; i < geometry.size(); i ++) indices.push_back(i);
    auto indexVBO = boost::make_shared<VBO>(true);
    indexVBO->setData(indices);
    vao->addVBO(indexVBO);

    renderable->addRenderSequence(boost::make_shared<RenderSequence>(
        ResourceRegistry::instance()->get<Technique>(technique), vao, 0,
        geometry.size()-1));

    Message3(Render, Debug, "Created Renderable from tri geom: "
        << renderable);
    Message3(Render, Debug, "Triangles: " << geometry.size()/3);

    return renderable;
}

}  // namespace Render
}  // namespace Kriti
