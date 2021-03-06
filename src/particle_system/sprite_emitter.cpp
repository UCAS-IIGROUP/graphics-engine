#include <particle_system/sprite_emitter.hpp>
#include <particle_system/unique_emitter.hpp>
#include <particle_system/emitter_visitor.hpp>

using namespace GraphicsEngine;

void GraphicsEngine::swap(SpriteEmitter &lhs, SpriteEmitter &rhs) noexcept {
    swap(static_cast<Emitter&>(lhs), static_cast<Emitter&>(rhs));

    using std::swap;

    swap(lhs.material, rhs.material);
}

SpriteEmitter::SpriteEmitter(SpriteEmitter&& emitter) noexcept
    : Emitter(std::move(emitter)) {
    swap(*this, emitter);
}

SpriteEmitter& SpriteEmitter::operator=(SpriteEmitter&& emitter) noexcept {
    Emitter::operator=(std::move(emitter));
    swap(*this, emitter);
    return *this;
}

SpriteEmitter* SpriteEmitter::clone() const noexcept {
    return new SpriteEmitter(*this);
}

void SpriteEmitter::accept(EmitterVisitor& visitor) noexcept {
    visitor.visit(*this);
}

UniqueSpriteEmitter SpriteEmitter::getEmitterType() const noexcept {
    std::vector<EmitterModuleType> mod;
    mod.reserve(modules.size());
    for (const auto& [type, module] : modules) {
        mod.emplace_back(type);
    }
    return { { mod }, material };
}

SpriteEmitter::SpriteEmitter() noexcept
    : Emitter{EmitterType::Sprite} {

}

SpriteEmitter::SpriteEmitter(EmitterType type) noexcept : Emitter(type) {

}
