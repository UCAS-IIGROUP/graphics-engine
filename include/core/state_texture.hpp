#pragma once

#include <core/extension_texture.hpp>
#include <core/texture_visitor.hpp>

namespace GraphicsEngine {
    class StateTexture : public ExtensionTexture {
    private:
        GLuint id {};
    public:
        StateTexture() noexcept;
        ~StateTexture() override;

        StateTexture(const StateTexture&) = delete;
        StateTexture& operator=(const StateTexture&) = delete;

        StateTexture(StateTexture&&) noexcept;
        StateTexture& operator=(StateTexture&&) noexcept;

        [[nodiscard]] StateTexture* clone() const override;

        void texStorage2D(GLenum target, GLsizei levels, GLenum internal_format, glm::uvec2 size) const noexcept override;
        void texStorage3D(GLenum target, GLsizei levels, GLenum internal_format, glm::uvec3 size) const noexcept override;
        void texStorage2DMultisample(GLenum target, uint8_t samples, GLenum internal_format, glm::uvec2 size) const noexcept override;

        void texImage2D(GLenum target, GLsizei levels, GLenum internal_format, GLenum format, GLenum type, glm::uvec2 size, const void* data) const noexcept override;
        void texImage3D(GLenum target, GLsizei levels, GLenum internal_format, GLenum format, GLenum type, glm::uvec3 size, const void *data) const noexcept override;
        void texImage2DMultiSample(GLenum target, uint8_t samples, GLenum internal_format, glm::uvec3 size) const noexcept override;

        void texSubImage2D(GLenum target, GLsizei levels, GLint xoffset, GLint yoffset, glm::uvec2 size, GLenum format, GLenum type, const void* data) const noexcept override;
        void texSubImage3D(GLenum target, GLsizei levels, GLint xoffset, GLint yoffset, GLint zoffset, glm::uvec3 size, GLenum format, GLenum type, const void* data) const noexcept override;

        void generateMipMap(GLenum target) const noexcept override;

        void activate(GLuint index) const noexcept;
        void bind(GLenum target, GLuint index) const noexcept override;

        void texParameter(GLenum target, GLenum name, GLint param) const noexcept override;
        void texParameter(GLenum target, GLenum name, GLfloat param) const noexcept override;
        void texParameter(GLenum target, GLenum name, GLint* params) const noexcept override;
        void texParameter(GLenum target, GLenum name, GLfloat* params) const noexcept override;

        void accept(TextureVisitor& visitor) noexcept override;

        [[nodiscard]] GLuint getId() const noexcept override { return id; }
    };
}