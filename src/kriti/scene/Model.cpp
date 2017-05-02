#include <boost/make_shared.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/material.h>
#include <assimp/mesh.h>

#include "Model.h"

#include "../FileResource.h"
#include "../ResourceRegistry.h"

#include "../AssimpWrapper.h"

namespace Kriti {
namespace Scene {

bool Model::loadFrom(std::string identifier) {
    Assimp::Importer importer;

    auto file = ResourceRegistry::get<FileResource>("models/" + identifier);
    if(!file) return false;

    const std::string &content = file->fileContent();

    const aiScene *result = importer.ReadFileFromMemory(
        content.c_str(), content.length(),
        aiProcess_Triangulate 
        | aiProcess_JoinIdenticalVertices
        | aiProcess_GenNormals
        | aiProcess_GenUVCoords
        | aiProcess_TransformUVCoords
        | aiProcess_OptimizeMeshes
    );

    if(!result) {
        Message3(Scene, Error, "Importing failed . . .");
        return false;
    }

    m_renderable = boost::make_shared<Render::Renderable>();

    if(!result->HasMaterials() && result->HasMeshes()) {
        Message3(Scene, Warning, "No materials, but have meshes. Default "
            "material will be used.");
    }
    else {
        for(int i = 0; i < result->mNumMaterials; i ++) {
            processMaterial(result, i);
        }
    }

    if(!result->HasMeshes()) {
        Message3(Scene, Debug, "Very strange . . . no meshes?");
    }
    else {
        for(int i = 0; i < result->mNumMeshes; i ++) {
            processMesh(result, i);
        }
    }

    processNode(result->mRootNode, Math::Matrix());

    return true;
}

void Model::processMaterial(const aiScene *scene, int index) {
    const aiMaterial *source = scene->mMaterials[index];

    auto dest = boost::make_shared<Render::Material>();
    // TODO: select better shader to load
    dest->loadFrom("simple_phong");
    m_materials.push_back(dest);

    // ambient
    aiColor3D colour;
    source->Get(AI_MATKEY_COLOR_AMBIENT, colour);
    dest->params().setParam("u_material.ambient",
        AssimpWrapper::convertColour(colour));

    // diffuse
    source->Get(AI_MATKEY_COLOR_DIFFUSE, colour);
    dest->params().setParam("u_material.diffuse",
        AssimpWrapper::convertColour(colour));

    // specular
    source->Get(AI_MATKEY_COLOR_SPECULAR, colour);
    dest->params().setParam("u_material.specular",
        AssimpWrapper::convertColour(colour));

    // shininess
    source->Get(AI_MATKEY_SHININESS, colour);
    dest->params().setParam("u_material.specularPower",
        AssimpWrapper::convertColour(colour));

    // specular scaling
    source->Get(AI_MATKEY_SHININESS_STRENGTH, colour);
    dest->params().setParam("u_material.specularScale",
        AssimpWrapper::convertColour(colour));
}

void Model::processMesh(const aiScene *scene, int index) {
    const aiMesh *mesh = scene->mMeshes[index];

    if(mesh->GetNumUVChannels() > 4) {
        Message3(Scene, Error, "More than 4 texture channels in model.");
        return;
    }
    if(mesh->GetNumColorChannels() > 4) {
        Message3(Scene, Error, "More than 4 colour channels in model.");
        return;
    }

    auto vao = boost::make_shared<Render::VAO>();
    int vao_size = mesh->mNumFaces*3; // each face is a triangle

    auto vertexVBO = boost::make_shared<Render::VBO>();
    auto normalVBO = boost::make_shared<Render::VBO>();
    std::vector<Math::Vector> vertv, normv;
    for(int i = 0; i < mesh->mNumVertices; i ++) {
        vertv.push_back(AssimpWrapper::convertVector(mesh->mVertices[i]));
        normv.push_back(AssimpWrapper::convertVector(mesh->mNormals[i]));
    }
    vertexVBO->setData3(vertv);
    normalVBO->setData3(normv);
    vao->addVBO(vertexVBO, Render::VAO::Vertex);
    vao->addVBO(normalVBO, Render::VAO::Normal);

    Render::VAO::Location cloc = Render::VAO::Colour0;

    for(int i = 0; i < mesh->GetNumColorChannels(); i ++) {
        std::vector<Math::Vector> colv;
        for(int j = 0; j < mesh->mNumVertices; j ++) {
            colv.push_back(AssimpWrapper::convertColour(mesh->mColors[i][j]));
        }
        cloc = (Render::VAO::Location)((int)cloc + 1);
    }

    Render::VAO::Location uvloc = Render::VAO::Texture0;

    for(int i = 0; i < mesh->GetNumUVChannels(); i ++) {
        std::vector<Math::Vector> texv;
        for(int j = 0; j < mesh->mNumVertices; j ++) {
            texv.push_back(
                AssimpWrapper::convertVector(mesh->mTextureCoords[i][j]));
        }
        auto texVBO = boost::make_shared<Render::VBO>();
        texVBO->setData3(texv);
        vao->addVBO(texVBO, uvloc);
        uvloc = (Render::VAO::Location)((int)uvloc + 1);
    }

    std::vector<unsigned int> facev;
    for(int i = 0; i < mesh->mNumFaces; i ++) {
        for(int j = 0; j < mesh->mFaces[i].mNumIndices; j ++) {
            facev.push_back(mesh->mFaces[i].mIndices[j]);
        }
    }

    auto facesVBO = boost::make_shared<Render::VBO>(Render::VBO::Element);
    facesVBO->setData(facev);

    vao->addVBO(facesVBO, Render::VAO::Element);

    auto seq = boost::make_shared<Render::RenderSequence>(
        m_materials[mesh->mMaterialIndex], vao, 0, facev.size()-1,
            Render::RenderSequence::Triangles,
            Render::RenderSequence::Indexed);

    m_meshes.push_back(seq);
}

void Model::processNode(const aiNode *node, Math::Matrix transform) {
    if(node == NULL) return;

    transform *= AssimpWrapper::convertMatrix(node->mTransformation);

    for(int i = 0; i < node->mNumMeshes; i ++) {
        // create copy of mesh render sequence
        Message3(Scene, Debug, "Mesh index: " << node->mMeshes[i]);
        auto seq = boost::make_shared<Render::RenderSequence>(
            *m_meshes[node->mMeshes[i]]);

        seq->sequenceTransform() = transform;

        m_renderable->addRenderSequence(seq);
    }

    Message3(Scene, Debug, "This node has " << node->mNumChildren << " children!");
    for(int i = 0; i < node->mNumChildren; i ++) {
        processNode(node->mChildren[i], transform);
    }
}

}  // namespace Scene
}  // namespace Kriti
