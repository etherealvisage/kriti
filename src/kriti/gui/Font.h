#ifndef KRITI_GUI__FONT_H
#define KRITI_GUI__FONT_H

#include <map>
#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "../render/Texture.h"

#include "../Resource.h"

namespace Kriti {
namespace GUI {

class Font : public Resource {
public:
    struct CharSpec {
        double tx, ty, tw, th; // texture coordinates
        double xoff, yoff, sw, sh, xadv, yadv; // screen coordinates
    };

    class Instance : public boost::enable_shared_from_this<Instance> {
    private:
        friend class Font;
        FT_Face m_face;
        std::vector<FT_Glyph_Metrics> &m_sizes;
        int m_ptSize;

        std::vector<FT_Glyph_Metrics> m_rawChars;
        std::vector<CharSpec> m_chars;

        boost::shared_ptr<Render::Texture> m_latestTexture;
        double m_baselineOffset;
    private:
        Instance(FT_Face face, std::vector<FT_Glyph_Metrics> &sizes,
            int ptSize);
    public:
        boost::shared_ptr<Render::Texture> texture()
            { return m_latestTexture; }
        void getCharSpec(int c, CharSpec &cs);
        double lineSpacing();
        double baselineOffset() const;
    };
private:
    FT_Face m_face;
    int m_fontHeight;
    std::vector<FT_Glyph_Metrics> m_sizes;
    std::map<int, boost::shared_ptr<Instance>> m_instances;
public:
    Font() {}

    virtual bool loadFrom(std::string identifier);

    boost::shared_ptr<Instance> getInstance(int ptSize);
};

}  // namespace GUI
}  // namespace Kriti

#endif
