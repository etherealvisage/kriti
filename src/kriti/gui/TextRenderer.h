#ifndef KRITI_GUI__TEXT_RENDERER_H
#define KRITI_GUI__TEXT_RENDERER_H

#include "Font.h"

#include "../render/Renderable.h"

namespace Kriti {
namespace GUI {

class TextRenderer {
public:
    class Block {
    private:
        std::string m_string;
        double m_width;
    public:
        Block(std::string string, double width) : m_string(string),
            m_width(width) {}

        double width() const { return m_width; }
    };

    enum BlockifyMode {
        Simple
    };
private:
    std::map<std::string, boost::shared_ptr<Font>> m_fonts;
    std::map<std::string, boost::shared_ptr<Font::Instance>> m_fontDefaults;
public:
    void addFont(boost::shared_ptr<Font> font, std::string name,
        int defaultSize);

    std::vector<Block> blockify(std::string text, BlockifyMode mode = Simple);

    boost::shared_ptr<Render::Renderable> renderString(
        boost::shared_ptr<Font::Instance> font, std::string s,
        Math::Vector colour = Math::Vector(1.0, 1.0, 1.0),
        Math::Vector scale = Math::Vector(1.0, 1.0));

    void sizeString(boost::shared_ptr<Font::Instance> font, std::string s,
        Math::Vector &ul, Math::Vector &lr);
};

}  // namespace GUI
}  // namespace Kriti

#endif
