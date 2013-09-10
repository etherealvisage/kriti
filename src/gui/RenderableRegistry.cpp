#include "RenderableRegistry.h"

namespace Kriti {
namespace GUI {

void RenderableRegistry::iterate(RenderableRegistry::FunctionType function) {
    for(auto renderable : m_renderables) {
        function(renderable);
    }
}

}  // namespace GUI
}  // namespace Kriti
