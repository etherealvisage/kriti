#ifndef KRITI_RENDER__CONSTANT_UNIFORM_HOOK_H
#define KRITI_RENDER__CONSTANT_UNIFORM_HOOK_H

#include "UniformHook.h"

namespace Kriti {
namespace Render {

class ConstantUniformHook : public UniformHook {
private:
    Uniforms m_uniforms;
public:
    Uniforms &uniforms() { return m_uniforms; }
    const Uniforms &uniforms() const { return m_uniforms; }
    
    virtual void hook(Uniforms &uniforms);
};

}  // namespace Render
}  // namespace Kriti

#endif
