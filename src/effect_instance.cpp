#include <effect_instance.hpp>
#include <particle_system/mesh_emitter.hpp>
#include <shader_types.hpp>

using namespace GraphicsEngine;

void GraphicsEngine::swap(EffectInstance& lhs, EffectInstance& rhs) noexcept {
    std::swap(lhs.emitters, rhs.emitters);
}

EffectInstance& EffectInstance::setPosition(const glm::vec3& _position) noexcept {
    AbstractInstance::setPosition(_position);

    for (auto& [name, emitter] : emitters) {
        emitter->setPosition(position);
    }

    return *this;
}

EffectInstance& EffectInstance::setRotation(const glm::vec3& _rotation) noexcept {
    AbstractInstance::setRotation(_rotation);

    for (auto& [name, emitter] : emitters) {
        emitter->setRotation(rotation);
    }

    return *this;
}

bool EffectInstance::isDone() const noexcept {
    bool done = true;
    for (const auto& [name, emitter] : emitters) {
        done &= emitter->isDone();
    }
    return done;
}

EffectInstance::EffectInstance(const EffectInstance& effect) noexcept
    : AbstractInstance{effect} {
    emitters.reserve(effect.emitters.size());
    for (const auto& [name, emitter] : effect.emitters) {
        emitters.emplace(name, emitter->clone());
    }
}

EffectInstance& EffectInstance::operator=(const EffectInstance& effect) noexcept {
    auto copied = EffectInstance{effect};
    *this = std::move(copied);
    return *this;
}

void EffectInstance::update() {
    AbstractInstance::update();
    // updates end of lifetime
    done = isDone();

    for (auto& [name, emitter] : emitters) {
        emitter->update();
    }
}

void EffectInstance::draw([[maybe_unused]] MaterialShader shader_type, [[maybe_unused]] Blending blending, [[maybe_unused]] const UniformSetter& uniform_set) {
    //throw std::runtime_error("One does not simply render effect instance!");
}

EffectInstance* EffectInstance::clone() noexcept {
    return new EffectInstance(*this);
}

EffectInstance::EffectInstance(Lighting *lighting, const std::shared_ptr<EffectInstance>& effect, const glm::vec3& position, const glm::vec3& rotation) noexcept
    : AbstractInstance{lighting, ModelShader::Effect, position, rotation, glm::vec3{0.0f}} {
    emitters.reserve(effect->emitters.size());
    for (const auto& [name, emitter] : effect->emitters) {
        emitters.emplace(name, emitter->clone());
    }

	EffectInstance::setPosition(position);
	EffectInstance::setRotation(rotation);
}

EffectInstance::EffectInstance(const std::shared_ptr<EffectInstance>& effect, const glm::vec3& position, const glm::vec3& rotation) noexcept
    : EffectInstance{nullptr, effect, position, rotation}  {
	EffectInstance::setPosition(position);
	EffectInstance::setRotation(rotation);
}

EffectInstance::EffectInstance() noexcept
    : AbstractInstance{ModelShader::Effect, glm::vec3{0.f}, glm::vec3{0.f}, glm::vec3{1.f}} {
}
