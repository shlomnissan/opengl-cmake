// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <glm/mat4x4.hpp>

class OrthographicCamera {
public:
    glm::mat4 transform {1.0f};

    OrthographicCamera(
        float left,
        float right,
        float bottom,
        float top,
        float near,
        float far
    );

    [[nodiscard]] auto& Projection() const {
        return projection_;
    }

    [[nodiscard]] auto& View() const {
        return view_;
    }

    auto OnUpdate() -> void;

private:
    glm::mat4 projection_ {1.0f};
    glm::mat4 view_ {1.0f};
};