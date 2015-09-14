#ifndef KRITI_RENDER__MATERIAL_H
#define KRITI_RENDER__MATERIAL_H

#include "Program.h"
#include "Uniforms.h"

#include "../Resource.h"

namespace Kriti {
namespace Render {

class Material : public Resource {
private:
    boost::shared_ptr<Program> m_program;
    Uniforms m_params;
public:
    Material() {}
    
    virtual bool loadFrom(std::string identifier);

    boost::shared_ptr<Program> program() const { return m_program; }
    Uniforms &params() { return m_params; }
    const Uniforms &params() const { return m_params; }
};

}  // namespace Render
}  // namespace Kriti

#endif
