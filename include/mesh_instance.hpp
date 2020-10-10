#pragma once

#include <material_instance.hpp>

namespace GraphicsEngine {
    class AbstractMesh;

    class MeshInstance {
    private:
        std::shared_ptr<AbstractMesh> mesh;
        MaterialInstance material;
        bool hidden {false};
    public:
        MeshInstance(std::shared_ptr<AbstractMesh> mesh, const std::shared_ptr<Material>& material) noexcept;

        [[nodiscard]] auto& getMaterial() noexcept { return material; }
        [[nodiscard]] bool isHidden() const noexcept { return hidden; }

        void hide() noexcept;
        void reveal() noexcept;

        void draw() const noexcept;
    };
}