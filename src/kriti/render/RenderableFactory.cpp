#include <boost/make_shared.hpp>

#include "RenderableFactory.h"

#include "VAO.h"
#include "VBO.h"

#include "../ResourceRegistry.h"
#include "../MessageSystem.h"

namespace Kriti {
namespace Render {

boost::shared_ptr<Renderable> RenderableFactory::fromModel(
    boost::shared_ptr<Model> model) {

    boost::shared_ptr<Renderable> renderable(new Renderable());

    /* Set up VAO. */
    boost::shared_ptr<VAO> vao(new VAO());

    boost::shared_ptr<VBO> vertexVBO(new VBO());
    vertexVBO->setData3(model->vertices());
    vao->addVBO(vertexVBO, VAO::Vertex);

    boost::shared_ptr<VBO> normalVBO(new VBO());
    normalVBO->setData3(model->normals());
    vao->addVBO(normalVBO, VAO::Normal);

    boost::shared_ptr<VBO> textureVBO(new VBO());
    textureVBO->setData2(model->texCoords());
    vao->addVBO(textureVBO, VAO::Texture0);

    boost::shared_ptr<VBO> indexVBO(new VBO(VBO::Element));
    indexVBO->setData(model->indices());
    vao->addVBO(indexVBO, VAO::Element);

    /* Create RenderSequence objects. */
    for(auto &ms : model->sequences()) {
        auto material = ResourceRegistry::get<Material>(
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
    vertexVBO->setData3(vertices);
    vao->addVBO(vertexVBO, VAO::Vertex);

    auto normalVBO = boost::make_shared<VBO>();
    normalVBO->setData3(normals);
    vao->addVBO(normalVBO, VAO::Normal);

    auto textureVBO = boost::make_shared<VBO>();
    textureVBO->setData2(texs);
    vao->addVBO(textureVBO, VAO::Texture0);

    auto indexVBO = boost::make_shared<VBO>(VBO::Element);
    indexVBO->setData(tris);
    vao->addVBO(indexVBO, VAO::Element);

    renderable->addRenderSequence(boost::make_shared<RenderSequence>(
        ResourceRegistry::get<Material>(material), vao, 0,
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
    vertexVBO->setData3(vertices);
    vao->addVBO(vertexVBO, VAO::Vertex);

    // zero normals.
    std::vector<Math::Vector> normals(vertices.size(), Math::Vector());
    auto normalVBO = boost::make_shared<VBO>();
    normalVBO->setData3(normals);
    vao->addVBO(normalVBO, VAO::Normal);

    auto textureVBO = boost::make_shared<VBO>();
    std::vector<Math::Vector> texs(vertices.size(), Math::Vector());
    textureVBO->setData2(texs);
    vao->addVBO(textureVBO, VAO::Texture0);

    std::vector<unsigned int> indices;
    for(unsigned i = 0; i < vertices.size(); i ++) indices.push_back(i);
    auto indexVBO = boost::make_shared<VBO>(VBO::Element);
    indexVBO->setData(indices);
    vao->addVBO(indexVBO, VAO::Element);

    renderable->addRenderSequence(boost::make_shared<RenderSequence>(
        ResourceRegistry::get<Material>(material), vao, 0,
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
    vertices.push_back(p1);
    vertices.push_back(p3);
    vertices.push_back(p4);
    vertexVBO->setData3(vertices);
    vao->addVBO(vertexVBO, VAO::Vertex);

    // TODO: make these actual normals...
    std::vector<Math::Vector> normals(vertices.size(), Math::Vector());
    auto normalVBO = boost::make_shared<VBO>();
    normalVBO->setData3(normals);
    vao->addVBO(normalVBO, VAO::Normal);

    auto textureVBO = boost::make_shared<VBO>();
    std::vector<Math::Vector> texs;
    texs.push_back(Math::Vector(0,0));
    texs.push_back(Math::Vector(0,1));
    texs.push_back(Math::Vector(1,1));

    texs.push_back(Math::Vector(0,0));
    texs.push_back(Math::Vector(1,1));
    texs.push_back(Math::Vector(1,0));
    textureVBO->setData2(texs);
    vao->addVBO(textureVBO, VAO::Texture0);

    std::vector<unsigned int> indices;
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(4);
    indices.push_back(5);
    auto indexVBO = boost::make_shared<VBO>(VBO::Element);
    indexVBO->setData(indices);
    vao->addVBO(indexVBO, VAO::Element);

    renderable->addRenderSequence(boost::make_shared<RenderSequence>(
        ResourceRegistry::get<Material>(material), vao, 0,
        indices.size()-1));

    return renderable;
}

boost::shared_ptr<Renderable> RenderableFactory::fromQuadGeometry(
    const std::vector<Math::Vector> &vertices,
    const std::vector<Math::Vector> &normals,
    const std::vector<Math::Vector> &texs,
    const std::vector<unsigned int> &quads, std::string material) {
    
    auto renderable = boost::make_shared<Renderable>();
    auto vao = boost::make_shared<VAO>();

    auto vertexVBO = boost::make_shared<VBO>();
    vertexVBO->setData3(vertices);
    vao->addVBO(vertexVBO, VAO::Vertex);

    auto normalVBO = boost::make_shared<VBO>();
    normalVBO->setData3(normals);
    vao->addVBO(normalVBO, VAO::Normal);

    auto textureVBO = boost::make_shared<VBO>();
    textureVBO->setData2(texs);
    vao->addVBO(textureVBO, VAO::Texture0);

    auto indexVBO = boost::make_shared<VBO>(VBO::Element);
    std::vector<unsigned int> tris;
    for(int i = 0; i < quads.size(); i += 4) {
        tris.push_back(quads[i]);
        tris.push_back(quads[i+1]);
        tris.push_back(quads[i+2]);

        tris.push_back(quads[i+2]);
        tris.push_back(quads[i+3]);
        tris.push_back(quads[i]);
    }
    indexVBO->setData(tris);
    vao->addVBO(indexVBO, VAO::Element);


    renderable->addRenderSequence(boost::make_shared<RenderSequence>(
        ResourceRegistry::get<Material>(material), vao, 0,
        tris.size()-1));

    /*Message3(Render, Debug, "Created Renderable from quad geom: "
        << renderable);
    Message3(Render, Debug, "Quads: " << quads.size()/4);*/

    return renderable;
}
    
}  // namespace Render
}  // namespace Kriti
