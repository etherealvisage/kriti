#ifndef KRITI_SCENE__MODEL_H
#define KRITI_SCENE__MODEL_H

#include <boost/shared_ptr.hpp>

#include "Resource.h"

#include "render/Renderable.h"

struct aiScene;

namespace Kriti {
namespace Scene {

class Model : public Resource {
private:
    std::vector<boost::shared_ptr<Render::Material>> m_materials;
    boost::shared_ptr<Render::Renderable> m_renderable;
public:
    /*Model();
    ~Model();*/

    virtual bool loadFrom(std::string identifier);
private:
    void processMaterial(const aiScene *scene, int index);
    void processMesh(const aiScene *scene, int index);
};

}  // namespace Scene
}  // namespace Kriti

#endif
