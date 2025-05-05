// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <glm/mat4x4.hpp>

class OrthographicCamera {
public:
    OrthographicCamera(
        float left,
        float right,
        float bottom,
        float top,
        float near,
        float far
    );

    [[nodiscard]] auto Projection() const -> const glm::mat4& {
        return projection_;
    }

private:
    glm::mat4 projection_ {1.0f};
};