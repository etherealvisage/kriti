#include "ConstantUniformHook.h"

#include "../math/Vector.h"

namespace Kriti {
namespace Render {

void ConstantUniformHook::hook(Uniforms &uniforms) {
    uniforms.add(m_uniforms);
}

}  // namespace Render
}  // namespace Kriti
