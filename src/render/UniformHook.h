#ifndef KRITI_RENDER__UNIFORM_HOOK_H
#define KRITI_RENDER__UNIFORM_HOOK_H

#include "Uniforms.h"

namespace Kriti {
namespace Render {

class UniformHook {
public:
    virtual ~UniformHook() {}

    virtual void hook(Uniforms &uniforms) = 0;
};

}  // namespace Render
}  // namespace Kriti

#endif
