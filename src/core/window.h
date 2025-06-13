// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <functional>
#include <string_view>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/timer.h"

class Window {
public:
    double mouse_pos_x {0.0};
    double mouse_pos_y {0.0};

    Window(int width, int height, std::string_view title);

    auto Start(const std::function<void(const double delta)>& program) -> void;

    ~Window();

private:
    GLFWwindow* window_ {nullptr};
    Timer timer_ {};
};