#include <effect_attachable.hpp>
#include <effect_instance.hpp>
#include <emitter.hpp>

using namespace GraphicsEngine;

EffectAttachable::Attachment::Attachment(const EffectInstance& _instance, const glm::vec3& _offset) noexcept
    : instance{std::make_unique<EffectInstance>(_instance)}, offset{_offset} {

}

EffectAttachable::Attachment::Attachment(EffectInstance&& _instance, const glm::vec3& _offset) noexcept
    : instance{std::make_unique<EffectInstance>(std::move(_instance))}, offset{_offset} {

}

EffectAttachable::Attachment& EffectAttachable::operator[](uint64_t index) noexcept {
    return attachments[index];
}

EffectAttachable::Attachment& EffectAttachable::at(uint64_t index) {
    return attachments.at(index);
}

EffectAttachable::Attachment::Attachment(const Attachment& attachment) noexcept
    : instance{attachment.instance->clone()}, offset{attachment.offset} {

}

EffectAttachable::Attachment& EffectAttachable::Attachment::operator=(const EffectAttachable::Attachment& attachment) noexcept {
    auto copied = Attachment{attachment};
    *this = std::move(copied);
    return *this;
}

EffectAttachable::Attachment::Attachment(EffectAttachable::Attachment&& attachment) noexcept
    : instance{std::move(attachment.instance)}, offset{attachment.offset} {

}

EffectAttachable::Attachment& EffectAttachable::Attachment::operator=(EffectAttachable::Attachment&& attachment) noexcept {
    instance = std::move(attachment.instance);
    offset = attachment.offset;
    return *this;
}

void EffectAttachable::detach(uint64_t index) noexcept {
    attachments.erase(attachments.begin() + index);
}

EffectAttachable::EffectAttachable() noexcept {
    // DO NOT REMOVE THIS
    //[[maybe_unused]] char empty;
}

EffectAttachable::~EffectAttachable() {
    // DO NOT REMOVE THIS
    //[[maybe_unused]] char empty;
}

EffectAttachable::EffectAttachable(const EffectAttachable& e) noexcept
    : attachments{e.attachments} {

}

EffectAttachable& EffectAttachable::operator=(const EffectAttachable& e) noexcept {
    attachments = e.attachments;
    return *this;
}

EffectAttachable::EffectAttachable(EffectAttachable&& e) noexcept
    : attachments{std::move(e.attachments)} {

}

EffectAttachable &EffectAttachable::operator=(EffectAttachable&& e) noexcept {
    attachments = std::move(e.attachments);
    return *this;
}

void EffectAttachable::update() {
    for (auto& [instance, offset] : attachments)
        instance->update();
}

void EffectAttachable::setPosition(const glm::vec3& position) noexcept {
    for (auto& [instance, offset] : attachments)
        instance->setPosition(position + offset);
}

void EffectAttachable::setRotation(const glm::vec3& rotation) noexcept {
    for (auto& [instance, offset] : attachments)
        instance->setRotation(rotation);
}

