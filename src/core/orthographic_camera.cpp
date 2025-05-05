// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "orthographic_camera.h"

#include <glm/gtc/matrix_transform.hpp>

OrthographicCamera::OrthographicCamera(
    float left,
    float right,
    float bottom,
    float top,
    float near,
    float far
) {
    projection_ = glm::ortho(left, right, bottom, top, near, far);
}