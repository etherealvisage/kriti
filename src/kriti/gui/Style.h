#ifndef KRITI_GUI__STYLE_H
#define KRITI_GUI__STYLE_H

#include <boost/shared_ptr.hpp>

#include "../math/Vector.h"
#include "../math/Colour.h"

#include "../render/Uniforms.fwd"

#include "../Resource.h"

namespace Kriti {
namespace GUI {

class Style : public Resource {
private:
    boost::shared_ptr<Render::Uniforms> m_uniforms;
public:
    Style();

    virtual bool loadFrom(std::string identifier);

    boost::shared_ptr<Render::Uniforms> uniforms() const { return m_uniforms; }
};

}  // namespace GUI
}  // namespace Kriti

#endif
