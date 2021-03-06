#pragma once

#include <core/shader_program.hpp>
#include <particle_system/emitter_renderer.hpp>

#include <shader_types.hpp>
#include <mutex>

namespace GraphicsEngine {
    struct ShaderKey {
        MaterialShader material_type;
        ModelShader model_type;
        uint64_t material_index;
    };
    bool operator<(const ShaderKey& lhs, const ShaderKey& rhs) noexcept;

    inline const std::map<MaterialShader, std::string> material_shader_path = {
        {MaterialShader::Default,           "pipeline/forward" },
        {MaterialShader::Deferred,          "pipeline/deferred" },
        {MaterialShader::ForwardPlus,       "pipeline/forward+" },
        {MaterialShader::DirectionalShadow, "shadows/directional" },
        {MaterialShader::PointShadow,       "shadows/point" },
        {MaterialShader::ColorPicker,       "other/color_picker" }
    };

    struct shader_storage_error : public std::runtime_error {
        explicit shader_storage_error(const std::string& error) : runtime_error(error) {}
    };

    class ShaderStorage {
    private:
        std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> shaders;
        std::map<ShaderKey, std::shared_ptr<ShaderProgram>> material_shaders;

        std::map<UniqueSpriteEmitter, std::shared_ptr<ShaderProgram>> sprite_emitter_shaders;
        std::map<UniqueMeshEmitter, std::shared_ptr<ShaderProgram>> mesh_emitter_shaders;
        std::mutex mutex;
    public:
        const std::shared_ptr<ShaderProgram>& get(const std::string& name) const;
        const std::shared_ptr<ShaderProgram>& get(MaterialShader material_type, ModelShader model_type, uint64_t material_index) const;
        const std::shared_ptr<ShaderProgram>& get(const UniqueSpriteEmitter& emitter_type) const;
        const std::shared_ptr<ShaderProgram>& get(const UniqueMeshEmitter& emitter_type) const;

        void add(std::string name, std::shared_ptr<ShaderProgram> program) noexcept;
        void add(MaterialShader material_type, ModelShader model_type, uint64_t material_index, std::shared_ptr<ShaderProgram> program) noexcept;
        void add(const UniqueSpriteEmitter& emitter_type, std::shared_ptr<ShaderProgram> program) noexcept;
        void add(const UniqueMeshEmitter& emitter_type, std::shared_ptr<ShaderProgram> program) noexcept;

        bool isExist(MaterialShader material_type, ModelShader model_type, uint64_t material_index) noexcept;

        void initialize();
    };

    inline ShaderStorage shader_storage;
}