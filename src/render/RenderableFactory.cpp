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
    vao->addVBO(vertexVBO, VAO::Vertex);

    boost::shared_ptr<VBO> normalVBO(new VBO());
    normalVBO->setData(model->normals());
    vao->addVBO(normalVBO, VAO::Normal);

    boost::shared_ptr<VBO> textureVBO(new VBO());
    textureVBO->setData(model->texCoords());
    vao->addVBO(textureVBO, VAO::Texture);

    boost::shared_ptr<VBO> indexVBO(new VBO(VBO::Element));
    indexVBO->setData(model->indices());
    vao->addVBO(indexVBO, VAO::Element);

    /* Create RenderSequence objects. */
    for(auto ms : model->sequences()) {
        auto material = ResourceRegistry::instance()->get<Material>(
            ms.materialName());
        boost::shared_ptr<RenderSequence> rs(new RenderSequence(material, vao,
            ms.start(), ms.end()));

        renderable->addRenderSequence(rs);
    }

    return renderable;
}

boost::shared_ptr<Renderable> RenderableFactory::fromTriangleGeometry(
    const std::vector<Math::Vector> &vertices,
    const std::vector<Math::Vector> &normals,
    const std::vector<unsigned int> &tris, std::string material) {

    std::vector<Math::Vector> texs;
    for(unsigned i = 0; i < tris.size(); i ++) {
        texs.push_back(Math::Vector());
    }
    return fromTriangleGeometry(vertices, normals, texs, tris, material);
}

boost::shared_ptr<Renderable> RenderableFactory::fromTriangleGeometry(
    const std::vector<Math::Vector> &vertices,
    const std::vector<Math::Vector> &normals,
    const std::vector<Math::Vector> &texs,
    const std::vector<unsigned int> &tris, std::string material) {
    
    auto renderable = boost::make_shared<Renderable>();
    auto vao = boost::make_shared<VAO>();

    auto vertexVBO = boost::make_shared<VBO>();
    vertexVBO->setData(vertices);
    vao->addVBO(vertexVBO, VAO::Vertex);

    auto normalVBO = boost::make_shared<VBO>();
    normalVBO->setData(normals);
    vao->addVBO(normalVBO, VAO::Normal);

    auto textureVBO = boost::make_shared<VBO>();
    textureVBO->setData(texs);
    vao->addVBO(textureVBO, VAO::Texture);

    auto indexVBO = boost::make_shared<VBO>(VBO::Element);
    indexVBO->setData(tris);
    vao->addVBO(indexVBO, VAO::Element);

    renderable->addRenderSequence(boost::make_shared<RenderSequence>(
        ResourceRegistry::instance()->get<Material>(material), vao, 0,
        tris.size()-1));

    Message3(Render, Debug, "Created Renderable from tri geom: "
        << renderable);
    Message3(Render, Debug, "Triangles: " << tris.size()/3);

    return renderable;
}

boost::shared_ptr<Renderable> RenderableFactory::fromLineGeometry(
    const std::vector<Math::Vector> &vertices, std::string material) {
    
    auto renderable = boost::make_shared<Renderable>();
    auto vao = boost::make_shared<VAO>();

    auto vertexVBO = boost::make_shared<VBO>();
    vertexVBO->setData(vertices);
    vao->addVBO(vertexVBO, VAO::Vertex);

    // zero normals.
    std::vector<Math::Vector> normals;
    for(auto v : vertices) normals.push_back(Math::Vector());
    auto normalVBO = boost::make_shared<VBO>();
    normalVBO->setData(normals);
    vao->addVBO(normalVBO, VAO::Normal);

    auto textureVBO = boost::make_shared<VBO>();
    std::vector<Math::Vector> texs;
    for(auto v : vertices) texs.push_back(Math::Vector());
    textureVBO->setData(texs);
    vao->addVBO(textureVBO, VAO::Texture);

    std::vector<unsigned int> indices;
    for(unsigned i = 0; i < vertices.size(); i ++) indices.push_back(i);
    auto indexVBO = boost::make_shared<VBO>(VBO::Element);
    indexVBO->setData(indices);
    vao->addVBO(indexVBO, VAO::Element);

    renderable->addRenderSequence(boost::make_shared<RenderSequence>(
        ResourceRegistry::instance()->get<Material>(material), vao, 0,
        vertices.size()-1, RenderSequence::Lines));

    return renderable;
}

boost::shared_ptr<Renderable> RenderableFactory::fromQuad(Math::Vector p1,
    Math::Vector p2, Math::Vector p3, Math::Vector p4, std::string material) {

    auto renderable = boost::make_shared<Renderable>();
    auto vao = boost::make_shared<VAO>();

    auto vertexVBO = boost::make_shared<VBO>();
    std::vector<Math::Vector> vertices;
    vertices.push_back(p1);
    vertices.push_back(p2);
    vertices.push_back(p3);
    vertices.push_back(p4);
    vertexVBO->setData(vertices);
    vao->addVBO(vertexVBO, VAO::Vertex);

    // TODO: make these actual normals...
    std::vector<Math::Vector> normals;
    for(auto v : vertices) normals.push_back(Math::Vector());
    auto normalVBO = boost::make_shared<VBO>();
    normalVBO->setData(normals);
    vao->addVBO(normalVBO, VAO::Normal);

    auto textureVBO = boost::make_shared<VBO>();
    std::vector<Math::Vector> texs;
    texs.push_back(Math::Vector(0,0));
    texs.push_back(Math::Vector(0,1));
    texs.push_back(Math::Vector(1,1));
    texs.push_back(Math::Vector(1,0));
    textureVBO->setData(texs);
    vao->addVBO(textureVBO, VAO::Texture);

    std::vector<unsigned int> indices;
    for(unsigned i = 0; i < vertices.size(); i ++) indices.push_back(i);
    auto indexVBO = boost::make_shared<VBO>(VBO::Element);
    indexVBO->setData(indices);
    vao->addVBO(indexVBO, VAO::Element);

    renderable->addRenderSequence(boost::make_shared<RenderSequence>(
        ResourceRegistry::instance()->get<Material>(material), vao, 0,
        vertices.size()-1, RenderSequence::Quads));

    return renderable;
}
    
}  // namespace Render
}  // namespace Kriti
