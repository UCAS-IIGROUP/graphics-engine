#include <light_attachable.hpp>

using namespace GraphicsEngine;

LightAttachable::LightAttachable(Lighting* _lighting) noexcept
    : lighting{_lighting} { }

LightAttachable::~LightAttachable() {
    for (const auto& [id, offset] : point_lights) {
        lighting->point_lights.erase(id);
    }

    for (const auto& [id, offset] : directional_lights)
        lighting->directional_lights.erase(id);

    for (const auto& [id, offset] : spot_lights)
        lighting->spot_lights.erase(id);
}

void LightAttachable::setPosition(const glm::vec3& position) noexcept {
    for (const auto& [id, offset] : point_lights)
        lighting->point_lights[id].position = { position + offset, 1.0f };

//            for (const auto& [id, offset] : spot_lights)
//                lighting->spot_lights[id].position = { position + offset, 1.0f };
}

void LightAttachable::setRotation(const glm::vec3& rotation) noexcept {
    for (const auto& [id, offset] : directional_lights)
        lighting->directional_lights[id].direction = { rotation, 1.0f };

//            for (const auto& [id, offset] : spot_lights)
//                lighting->spot_lights[id].position = { position + offset, 1.0f };
}
