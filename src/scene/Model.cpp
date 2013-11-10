#include <boost/make_shared.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/material.h>
#include <assimp/mesh.h>

#include "Model.h"

#include "FileResource.h"
#include "ResourceRegistry.h"

#include "AssimpWrapper.h"

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

    return false;
}

void Model::processMaterial(const aiScene *scene, int index) {
    const aiMaterial *source = scene->mMaterials[index];

    auto dest = boost::make_shared<Render::Material>();
    m_materials.push_back(dest);

    // ambient
    aiColor3D colour;
    source->Get(AI_MATKEY_COLOR_AMBIENT, colour);
    dest->params().setParam("u_ambient", AssimpWrapper::convertColour(colour));

    // diffuse
    source->Get(AI_MATKEY_COLOR_DIFFUSE, colour);
    dest->params().setParam("u_diffuse", AssimpWrapper::convertColour(colour));

    // specular
    source->Get(AI_MATKEY_COLOR_SPECULAR, colour);
    dest->params().setParam("u_specular",
        AssimpWrapper::convertColour(colour));

    // shininess
    source->Get(AI_MATKEY_SHININESS, colour);
    dest->params().setParam("u_specularPower",
        AssimpWrapper::convertColour(colour));

    // specular scaling
    source->Get(AI_MATKEY_SHININESS_STRENGTH, colour);
    dest->params().setParam("u_specularScale",
        AssimpWrapper::convertColour(colour));
}

void Model::processMesh(const aiScene *scene, int index) {
    const aiMesh *mesh = scene->mMeshes[index];

    /*Message3(Scene, Debug, "Mesh channels: " << mesh->GetNumColorChannels()
        << "/" << mesh->GetNumUVChannels());*/

    auto vao = boost::make_shared<Render::VAO>();
    int vao_size = mesh->mNumFaces;

    auto seq = boost::make_shared<Render::RenderSequence>(
        m_materials[mesh->mMaterialIndex], vao, 0, vao_size-1);
    m_renderable->addRenderSequence(seq);
}

}  // namespace Scene
}  // namespace Kriti
