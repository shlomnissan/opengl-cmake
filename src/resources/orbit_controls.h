// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "core/events.h"
#include "core/event_dispatcher.h"
#include "core/perspective_camera.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <memory>

class OrbitControls {
public:
    float radius {1.0f};
    float pitch {0.0f};
    float yaw {0.0f};

    float orbit_speed {5.0f};
    float zoom_speed {50.0f};
    float pan_speed {1.5f};

    explicit OrbitControls(PerspectiveCamera* camera);

    auto OnUpdate(float delta) -> void;

private:
    glm::vec3 target {0.0f};
    glm::vec2 curr_mouse_pos_ {0.0f};
    glm::vec2 prev_mouse_pos_ {0.0f};

    float curr_scroll_offset_ {0.0f};

    MouseButton curr_mouse_button_ {MouseButton::None};

    PerspectiveCamera* camera_;

    std::shared_ptr<EventListener> event_listener_;

    bool first_update_ {false};

    auto OnMouseEvent(MouseEvent* event) -> void;

    auto Orbit(const glm::vec2& offset, float delta) -> void;

    auto Pan(const glm::vec2& offset, float delta) -> void;

    auto Zoom(const float scroll_offset, float delta) -> void;
};