#ifndef KRITI_RENDER__MODEL_SEQUENCE_H
#define KRITI_RENDER__MODEL_SEQUENCE_H

#include <string>

namespace Kriti {
namespace Render {

class ModelSequence {
private:
    std::string m_materialName;
    int m_start, m_end;
public:
    ModelSequence(std::string materialName, int start, int end)
        : m_materialName(materialName), m_start(start), m_end(end) {}

    std::string materialName() const { return m_materialName; }

    int start() const { return m_start; }
    int end() const { return m_end; }
};

}  // namespace Render
}  // namespace Kriti

#endif
