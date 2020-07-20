#pragma once

#include <bindless_texture.hpp>
#include <context_initializer.hpp>

namespace GraphicsEngine {
    class TextureBuilder {
    public:
        static std::unique_ptr<Texture> build(Texture::Type target, Texture::InternalFormat internal, glm::uvec2 size, Texture::Format format, Texture::DataType data_type, const void* data = nullptr) {
            std::unique_ptr<Texture> texture;

            if (ContextInitializer::isExtensionSupported("GL_ARB_direct_state_access")) {
                texture = std::make_unique<NamedTexture>(target, internal, size, format, data_type, data);
            } else {
                texture = std::make_unique<StateTexture>(target, internal, size, format, data_type, data);
            }

            if (ContextInitializer::isExtensionSupported("GL_ARB_bindless_texture")) {
                return std::unique_ptr<Texture>(new BindlessTexture(std::move(texture)));
            }

            return texture;
        }

        static std::unique_ptr<Texture> build(Texture::Type target, Texture::InternalFormat internal, glm::uvec3 size, Texture::Format format, Texture::DataType data_type, const void* data = nullptr) {
            std::unique_ptr<Texture> texture;

            if (ContextInitializer::isExtensionSupported("GL_ARB_direct_state_access")) {
                texture = std::make_unique<NamedTexture>(target, internal, size, format, data_type, data);
            } else {
                texture = std::make_unique<StateTexture>(target, internal, size, format, data_type, data);
            }

            if (ContextInitializer::isExtensionSupported("GL_ARB_bindless_texture")) {
                return std::unique_ptr<Texture>(new BindlessTexture(std::move(texture)));
            }

            return texture;
        }

        static std::unique_ptr<Texture> build(Texture::Type target, Texture::InternalFormat internal, glm::uvec2 size, Texture::Format format, Texture::DataType data_type, const std::array<void*, 6>& data) {
            std::unique_ptr<Texture> texture;

            if (ContextInitializer::isExtensionSupported("GL_ARB_direct_state_access")) {
                texture = std::make_unique<NamedTexture>(target, internal, size, format, data_type, data);
            } else {
                texture = std::make_unique<StateTexture>(target, internal, size, format, data_type, data);
            }

            if (ContextInitializer::isExtensionSupported("GL_ARB_bindless_texture")) {
                return std::unique_ptr<Texture>(new BindlessTexture(std::move(texture)));
            }

            return texture;
        }

        static std::unique_ptr<Texture> build(Texture::Type target, GLsizei levels, Texture::InternalFormat internal, glm::uvec2 size, Texture::Format format, Texture::DataType data_type, const void* data = nullptr) {
            std::unique_ptr<Texture> texture;

            if (ContextInitializer::isExtensionSupported("GL_ARB_texture_storage")) {
                if (ContextInitializer::isExtensionSupported("GL_ARB_direct_state_access")) {
                    texture = std::make_unique<NamedTexture>(target, levels, internal, size, format, data_type, data);
                } else {
                    texture = std::make_unique<StateTexture>(target, levels, internal, size, format, data_type, data);
                }
            } else {
                if (ContextInitializer::isExtensionSupported("GL_ARB_direct_state_access")) {
                    texture = std::make_unique<NamedTexture>(target, internal, size, format, data_type, data);
                } else {
                    texture = std::make_unique<StateTexture>(target, internal, size, format, data_type, data);
                }
            }

            if (ContextInitializer::isExtensionSupported("GL_ARB_bindless_texture")) {
                return std::unique_ptr<Texture>(new BindlessTexture(std::move(texture)));
            }

            return texture;
        }

        static std::unique_ptr<Texture> build(Texture::Type target, GLsizei levels, Texture::InternalFormat internal, glm::uvec3 size, Texture::Format format, Texture::DataType data_type, const void* data) {
            std::unique_ptr<Texture> texture;

            if (ContextInitializer::isExtensionSupported("GL_ARB_texture_storage")) {
                if (ContextInitializer::isExtensionSupported("GL_ARB_direct_state_access")) {
                    texture = std::make_unique<NamedTexture>(target, levels, internal, size, format, data_type, data);
                } else {
                    texture = std::make_unique<StateTexture>(target, levels, internal, size, format, data_type, data);
                }
            } else {
                if (ContextInitializer::isExtensionSupported("GL_ARB_direct_state_access")) {
                    texture = std::make_unique<NamedTexture>(target, internal, size, format, data_type, data);
                } else {
                    texture = std::make_unique<StateTexture>(target, internal, size, format, data_type, data);
                }
            }

            if (ContextInitializer::isExtensionSupported("GL_ARB_bindless_texture")) {
                return std::unique_ptr<Texture>(new BindlessTexture(std::move(texture)));
            }

            return texture;
        }

        static std::unique_ptr<Texture> build(Texture::Type target, GLsizei levels, Texture::InternalFormat internal, glm::uvec2 size, Texture::Format format, Texture::DataType data_type, const std::array<void*, 6>& data = { nullptr }) {
            std::unique_ptr<Texture> texture;

            if (ContextInitializer::isExtensionSupported("GL_ARB_texture_storage")) {
                if (ContextInitializer::isExtensionSupported("GL_ARB_direct_state_access")) {
                    texture = std::make_unique<NamedTexture>(target, levels, internal, size, format, data_type, data);
                } else {
                    texture = std::make_unique<StateTexture>(target, levels, internal, size, format, data_type, data);
                }
            } else {
                if (ContextInitializer::isExtensionSupported("GL_ARB_direct_state_access")) {
                    texture = std::make_unique<NamedTexture>(target, internal, size, format, data_type, data);
                } else {
                    texture = std::make_unique<StateTexture>(target, internal, size, format, data_type, data);
                }
            }

            if (ContextInitializer::isExtensionSupported("GL_ARB_bindless_texture")) {
                return std::unique_ptr<Texture>(new BindlessTexture(std::move(texture)));
            }

            return texture;
        }

        static std::unique_ptr<Texture> build(Texture::Type target, uint8_t samples, Texture::InternalFormat internal, glm::uvec2 size, bool immutable = false) {
            std::unique_ptr<Texture> texture;
            bool imm = immutable & ContextInitializer::isExtensionSupported("GL_ARB_texture_storage");

            if (ContextInitializer::isExtensionSupported("GL_ARB_direct_state_access")) {
                texture = std::make_unique<NamedTexture>(target, samples, internal, size, imm);
            } else {
                texture = std::make_unique<StateTexture>(target, samples, internal, size, imm);
            }

            if (ContextInitializer::isExtensionSupported("GL_ARB_bindless_texture")) {
                return std::unique_ptr<Texture>(new BindlessTexture(std::move(texture)));
            }

            return texture;
        }
    };
}