#ifndef KRITI_SCENE__MODEL_H
#define KRITI_SCENE__MODEL_H

#include <boost/shared_ptr.hpp>

#include "../Resource.h"

#include "../render/Renderable.h"

struct aiScene;
struct aiNode;
struct aiMaterial;

namespace Kriti {
namespace Scene {

class Model : public Resource {
private:
    std::vector<boost::shared_ptr<Render::Material>> m_materials;
    std::vector<boost::shared_ptr<Render::RenderSequence>> m_meshes;
    boost::shared_ptr<Render::Renderable> m_renderable;
public:
    /*Model();
    ~Model();*/

    boost::shared_ptr<Render::Renderable> renderable() const
        { return m_renderable; }

    virtual bool loadFrom(std::string identifier);
private:
    void processMaterial(const aiScene *scene, int index);
    void processMaterialStack(const aiMaterial *source,
        const boost::shared_ptr<Render::Material> &dest,
        int typeInt, std::string destName);
    void processMesh(const aiScene *scene, int index);
    void processNode(const aiNode *node, Math::Matrix transform);
};

}  // namespace Scene
}  // namespace Kriti

#endif
