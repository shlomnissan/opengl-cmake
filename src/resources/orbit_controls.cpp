// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "orbit_controls.h"

#include <algorithm>
#include <cmath>

#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

constexpr auto kVerticalLimit = glm::half_pi<float>() - 0.1f;

OrbitControls::OrbitControls(PerspectiveCamera* camera) : camera_(camera) {
    event_listener_ = std::make_shared<EventListener>([this](Event* event) {
        if (const auto e = dynamic_cast<MouseEvent*>(event)) {
            OnMouseEvent(e);
        }
    });
    EventDispatcher::Get().AddEventListener("mouse_event", event_listener_);
}

auto OrbitControls::OnMouseEvent(MouseEvent* event) -> void {
    using enum MouseButton;
    using enum MouseEvent::Type;

    curr_mouse_pos_ = event->position;

    if (event->type == ButtonPressed && curr_mouse_button_ == None) {
        curr_mouse_button_ = event->button;
    }

    if (event->type == ButtonReleased && event->button == curr_mouse_button_) {
        curr_mouse_button_ = None;
    }

    if (event->type == Scrolled) {
        curr_scroll_offset_ = event->scroll.y;
    }
}

auto OrbitControls::OnUpdate(float delta) -> void {
    if (!first_update_) {
        first_update_ = true;
        prev_mouse_pos_ = curr_mouse_pos_;
        return;
    }

    const auto mouse_offset = curr_mouse_pos_ - prev_mouse_pos_;

    if (curr_mouse_button_ == MouseButton::Left) {
        Orbit(mouse_offset, delta);
    }

    if (curr_mouse_button_ == MouseButton::Right) {
        Pan(mouse_offset, delta);
    }

    if (curr_scroll_offset_ != 0.0f) {
        Zoom(curr_scroll_offset_, delta);
        curr_scroll_offset_ = 0.0f;
    }

    prev_mouse_pos_ = curr_mouse_pos_;

    // convert spherical coordinates to cartesian coordinates
    const auto position = target + glm::vec3 {
        radius * std::sin(yaw) * std::cos(pitch),
        radius * std::sin(pitch),
        radius * std::cos(yaw) * std::cos(pitch)
    };

    camera_->transform[3] = glm::vec4 {position, 1.0f};
    camera_->transform = glm::inverse(
        glm::lookAt(position, target, {0.0f, 1.0f, 0.0f})
    );
}

auto OrbitControls::Orbit(const glm::vec2& offset, float delta) -> void {
    yaw -= offset.x * orbit_speed * delta;
    pitch += offset.y * orbit_speed * delta;
    pitch = std::clamp(pitch, -kVerticalLimit, kVerticalLimit);
}

auto OrbitControls::Pan(const glm::vec2& offset, float delta) -> void {
    const auto forward = glm::normalize(glm::vec3(camera_->transform[3]) - target);
    const auto right = glm::normalize(glm::cross(forward, {0.0f, 1.0f, 0.0}));
    const auto up = glm::cross(right, forward);

    const auto pan_h = right * offset.x * pan_speed * delta;
    const auto pan_v = up * offset.y * pan_speed * delta;

    target += pan_h + pan_v;
}

auto OrbitControls::Zoom(const float scroll_offset, float delta) -> void {
    radius -= scroll_offset * zoom_speed * delta;
    radius = std::max(0.1f, radius);
}