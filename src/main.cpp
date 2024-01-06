// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <array>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core/mesh.h"
#include "core/shader.h"
#include "core/window.h"

#include "shaders/headers/vertex.h"
#include "shaders/headers/fragment.h"

#include "mesh/cube.h"

auto main() -> int {
    auto window = Window {800, 600, "OpenGL starter project"};

    auto shader = Shader {{
        {ShaderType::kVertexShader, _SHADER_vertex},
        {ShaderType::kFragmentShader, _SHADER_fragment}
    }};
    
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    shader.Use();
    shader.SetMat4(
        "Projection",
        glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f)
    );

    auto view = glm::lookAt(
        glm::vec3{0.0f, 0.0f, 1.0f},
        glm::vec3{0.0f, 0.0f, 0.0f},
        glm::vec3{0.0f, 1.0f, 0.0f}
    );

    auto cube = Mesh {cube_vertex_0, cube_index_0};

    window.Start([&](const double delta){
        glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto model = glm::mat4{1.0f};
        model = glm::scale(model, {0.3f, 0.3f, 0.3f});
        model = glm::rotate(model, static_cast<float>(glfwGetTime()), {1.0f, 1.0f, 1.0f});
        shader.SetMat4("ModelView", view * model);

        cube.Draw(shader); 
    });

    return 0;
}