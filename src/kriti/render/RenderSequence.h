#ifndef KRITI_RENDER__RENDER_SEQUENCE_H
#define KRITI_RENDER__RENDER_SEQUENCE_H

#include "Material.h"
#include "VAO.h"

#include "../math/Matrix.h"

namespace Kriti {
namespace Render {

class RenderSequence {
public:
    enum RenderType {
        Lines,
        Triangles
    };
    enum RenderMode {
        Sequential,
        Indexed
    };
private:
    boost::shared_ptr<Material> m_material;
    int m_start, m_end;
    boost::shared_ptr<VAO> m_vao;
    RenderType m_type;
    RenderMode m_mode;
    Uniforms m_extraParams;
    Math::Matrix m_sequenceTransform;
public:
    RenderSequence(boost::shared_ptr<Material> material,
        boost::shared_ptr<VAO> vao, int start, int end,
        RenderType type = Triangles, RenderMode mode = Indexed)
        : m_material(material), m_start(start), m_end(end), m_vao(vao),
            m_type(type), m_mode(mode) {}

    boost::shared_ptr<VAO> vao() const { return m_vao; }
    int start() const { return m_start; }
    int end() const { return m_end; }

    void updateRange(int start, int end) { m_start = start, m_end = end; }

    Uniforms &extraParams() { return m_extraParams; }
    const Uniforms &extraParams() const { return m_extraParams; }

    Math::Matrix &sequenceTransform() { return m_sequenceTransform; }
    const Math::Matrix &sequenceTransform() const
        { return m_sequenceTransform; }

    void draw(const Uniforms &params,
        std::map<boost::weak_ptr<Material>, Uniforms> &materialParams,
        const Math::Matrix &modelTransformation);
};

}  // namespace Render
}  // namespace Kriti

#endif
