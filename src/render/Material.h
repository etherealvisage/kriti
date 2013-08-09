#ifndef KRITI_RENDER__MATERIAL_H
#define KRITI_RENDER__MATERIAL_H

#include "Technique.h"
#include "TechniqueParams.h"

#include "Resource.h"

namespace Kriti {
namespace Render {

class Material : public Resource {
private:
    std::string m_techniqueName;
    boost::shared_ptr<Technique> m_technique;
    TechniqueParams m_params;
public:
    Material() {}
    Material(std::string techniqueName, TechniqueParams params)
        : m_techniqueName(techniqueName), m_params(params) {}
    
    virtual bool loadFrom(std::string identifier);

    std::string techniqueName() const { return m_techniqueName; }
    boost::shared_ptr<Technique> technique() const { return m_technique; }
    TechniqueParams &params() { return m_params; }
    const TechniqueParams &params() const { return m_params; }
};

}  // namespace Render
}  // namespace Kriti

#endif
