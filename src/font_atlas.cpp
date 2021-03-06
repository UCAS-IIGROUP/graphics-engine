#include <font_atlas.hpp>

using namespace GraphicsEngine;
using namespace std::literals::string_literals;

FontAtlas::FontAtlas(const fs::path& path, uint32_t size) {
    static FT_Library ft {nullptr};

    if (!ft) {
        if (FT_Init_FreeType(&ft)) {
            throw font_error{"Failed to initialize Freetype"};
        }
    }

    if (FT_New_Face(ft, path.string().c_str(), 0, &face)) {
        throw font_error{"Failed to load the font at path"s + path.string()};
    }

    FT_Set_Pixel_Sizes(face, 0, size);

    uint32_t max_width {0};
    uint32_t max_height {0};
    uint64_t total_area {0};

    for (char c = 0; c < 127; ++c) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            throw font_error{"Failed to load glyph"};
        }

        max_width = std::max(max_width, face->glyph->bitmap.width);
        max_height = std::max(max_height, face->glyph->bitmap.rows);

        total_area += face->glyph->bitmap.rows * face->glyph->bitmap.width;
    }

    const glm::uvec2 side_size {512, 512};
    //const glm::uvec2 side_size = {max_width * size, max_height * size};

    std::vector<std::byte> data(side_size.x * side_size.y);

    uint32_t x {0};
    uint32_t y {0};
    for (char c = 0; c < 127; ++c) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            throw font_error{"Failted to load character"};
        }

        const auto glyph_w = face->glyph->bitmap.width;
        const auto glyph_h = face->glyph->bitmap.rows;
        const auto glyph_pitch = face->glyph->bitmap.pitch;

        if (x + glyph_w >= side_size.x) {
            x = 0;
            y += max_height;
        }

        for (uint32_t i = 0; i < glyph_h; ++i) {
            memcpy(data.data() + side_size.x * (i + y) + x, face->glyph->bitmap.buffer + glyph_pitch * i, glyph_w);
        }

        chars.emplace(c, FontCharacter{
            {glyph_w, glyph_h},
            {face->glyph->bitmap_left, face->glyph->bitmap_top},
            static_cast<uint32_t>(face->glyph->advance.x),
            {
               glm::vec2{ (float)x / (float)side_size.x, (float)(y + glyph_h) / (float)side_size.y},
               glm::vec2{(float)(x + glyph_w) / (float)side_size.x, (float)(y + glyph_h) / (float)side_size.y},
               glm::vec2{(float)x / (float)side_size.x, (float)y / (float)side_size.y},
               glm::vec2{(float)(x + glyph_w) / (float)side_size.x, (float)y / (float)side_size.y}
            }}
        );

        x += glyph_w;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //TODO: make it immutable?
    auto params = [] (Texture& tex) {
        tex << TexParameter<GLint>{GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE}
            << TexParameter<GLint>{GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE}
            << TexParameter<GLint>{GL_TEXTURE_MIN_FILTER, GL_LINEAR}
            << TexParameter<GLint>{GL_TEXTURE_MAG_FILTER, GL_LINEAR};
    };
    texture = TextureBuilder::build(Texture::Type::Tex2D, Texture::InternalFormat::R, side_size, Texture::Format::Red, Texture::DataType::UnsignedByte, data.data(), std::move(params));
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

FontAtlas::~FontAtlas() {
    if (face) {
        FT_Done_Face(face);
    }
}

std::vector<TextVertex> FontAtlas::generate(const std::string& text) const {
    std::vector<TextVertex> vertices;
    vertices.reserve(text.size());

    glm::vec2 offset {0.f, 0.f};
    for (const auto c : text) {
        auto& fc = chars.at(c);

        float x = offset.x + fc.bearing.x;
        float y = offset.y + fc.bearing.y - fc.size.y;

        vertices.emplace_back(glm::vec2{x, y + fc.size.y}, fc.uvs[2]);
        vertices.emplace_back(glm::vec2{x, y},             fc.uvs[0]);
        vertices.emplace_back(glm::vec2{x + fc.size.x, y}, fc.uvs[1]);

        vertices.emplace_back(glm::vec2{x, y + fc.size.y}, fc.uvs[2]);
        vertices.emplace_back(glm::vec2{x + fc.size.x, y}, fc.uvs[1]);
        vertices.emplace_back(glm::vec2{x + fc.size.x, y + fc.size.y}, fc.uvs[3]);

        offset.x += (fc.advance >> 6);
    }

    return vertices;
}
