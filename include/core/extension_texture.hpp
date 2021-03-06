#pragma once

#include <core/context_debug.hpp>
#include <core/texture_visitor.hpp>
#include <glm/glm.hpp>

namespace GraphicsEngine {
    class ExtensionTexture {
    public:
        ExtensionTexture() = default;
        virtual ~ExtensionTexture() = default;

        ExtensionTexture(const ExtensionTexture&) = delete;
        ExtensionTexture& operator=(const ExtensionTexture&) = delete;

        ExtensionTexture(ExtensionTexture&&) noexcept = default;
        ExtensionTexture& operator=(ExtensionTexture&&) noexcept = default;

        // clones extension texture; returns new generated one
        [[nodiscard]] virtual ExtensionTexture* clone() const = 0;

        // immutable storage allocation interface
        virtual void texStorage2D(GLenum target, GLsizei levels, GLenum internal_format, glm::uvec2 size) const noexcept = 0;
        virtual void texStorage3D(GLenum target, GLsizei levels, GLenum internal_format, glm::uvec3 size) const noexcept = 0;
        virtual void texStorage2DMultisample(GLenum target, uint8_t samples, GLenum internal_format, glm::uvec2 size) const noexcept = 0;

        // mutable storage allocation&loading interface
        virtual void texImage2D(GLenum target, GLsizei levels, GLenum internal_format, GLenum format, GLenum type, glm::uvec2 size, const void* data) const noexcept = 0;
        virtual void texImage3D(GLenum target, GLsizei levels, GLenum internal_format, GLenum format, GLenum type, glm::uvec3 size, const void *data) const noexcept = 0;
        virtual void texImage2DMultiSample(GLenum target, uint8_t samples, GLenum internal_format, glm::uvec3 size) const noexcept = 0;

        // common loading interface
        virtual void texSubImage2D(GLenum target, GLsizei levels, GLint xoffset, GLint yoffset, glm::uvec2 size, GLenum format, GLenum type, const void* data) const noexcept = 0;
        virtual void texSubImage3D(GLenum target, GLsizei levels, GLint xoffset, GLint yoffset, GLint zoffset, glm::uvec3 size, GLenum format, GLenum type, const void* data) const noexcept = 0;

        // mipmap generation
        virtual void generateMipMap(GLenum target) const noexcept = 0;

        // binds texture to specified index
        virtual void bind(GLenum target, GLuint index) const noexcept = 0;

        // sets various of parameters
        virtual void texParameter(GLenum target, GLenum name, GLint param) const noexcept = 0;
        virtual void texParameter(GLenum target, GLenum name, GLfloat param) const noexcept = 0;
        virtual void texParameter(GLenum target, GLenum name, GLint* params) const noexcept = 0;
        virtual void texParameter(GLenum target, GLenum name, GLfloat* params) const noexcept = 0;

        virtual void accept(TextureVisitor& visitor) noexcept = 0;

        [[nodiscard]] virtual GLuint getId() const noexcept = 0;
    };
}