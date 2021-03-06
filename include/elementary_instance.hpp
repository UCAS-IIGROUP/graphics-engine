#pragma once

#include <model_instance.hpp>

namespace GraphicsEngine {
    class ElementaryInstance : public AbstractInstance {
    protected:
        std::shared_ptr<AbstractModel> model;
        MeshInstance mesh;
        glm::mat4 model_matrix;

        void calculateModelMatrix() noexcept;
    public:
        ElementaryInstance(decltype(model) model, std::shared_ptr<Material> material, const glm::vec3& position, const glm::vec3& rotation = glm::vec3{0.0f}, const glm::vec3& scale = glm::vec3{1.0f});
        ElementaryInstance(Lighting* lighting, decltype(model) model, std::shared_ptr<Material> material, const glm::vec3& position, const glm::vec3& rotation = glm::vec3{0.0f}, const glm::vec3& scale = glm::vec3{1.0f});

        ~ElementaryInstance() override = default;

        ElementaryInstance(const ElementaryInstance&) = default;
        ElementaryInstance& operator=(const ElementaryInstance&) = default;

        ElementaryInstance(ElementaryInstance&&) noexcept = default;
        ElementaryInstance& operator=(ElementaryInstance&&) noexcept = default;

        [[nodiscard]] ElementaryInstance* clone() noexcept override;

        [[nodiscard]] MeshInstance& getMesh() noexcept { return mesh; }
        [[nodiscard]] const MeshInstance& getMesh() const noexcept { return mesh; }

        using AbstractInstance::draw;
        void draw(MaterialShader shader_type, Blending blending, const UniformSetter& uniform_setter) override;
    };
}