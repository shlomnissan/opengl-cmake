// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include <array>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core/geometry.h"
#include "core/perspective_camera.h"
#include "core/shaders.h"
#include "core/window.h"

#include "shaders/headers/scene_vert.h"
#include "shaders/headers/scene_frag.h"

#include "geometries/box_geometry.h"

auto main() -> int {
    const auto win_width = 1024;
    const auto win_height = 768;
    auto window = Window {win_width, win_height, "OpenGL starter project"};
    auto ratio = static_cast<float>(win_width) / static_cast<float>(win_height);
    auto camera = PerspectiveCamera {45.0f, ratio, 0.1f, 100.0f};

    auto shader = Shaders {{
        {ShaderType::kVertexShader, _SHADER_scene_vert},
        {ShaderType::kFragmentShader, _SHADER_scene_frag}
    }};

    glEnable(GL_DEPTH_TEST);

    auto view = glm::lookAt(
        glm::vec3{0.0f, 0.0f, 1.0f},
        glm::vec3{0.0f, 0.0f, 0.0f},
        glm::vec3{0.0f, 1.0f, 0.0f}
    );

    auto cube = BoxGeometry({
        .width = 1.0f,
        .height = 1.0f,
        .depth = 1.0f,
        .width_segments = 1,
        .height_segments = 1,
        .depth_segments = 1
    });

    window.Start([&](const double _){
        glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto model = glm::mat4{1.0f};
        model = glm::scale(model, {0.3f, 0.3f, 0.3f});
        model = glm::rotate(model, static_cast<float>(glfwGetTime()), {1.0f, 1.0f, 1.0f});

        shader.SetUniform("Projection", camera.Projection());
        shader.SetUniform("ModelView", view * model);

        cube.Draw(shader);
    });

    return 0;
}