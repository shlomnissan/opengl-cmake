// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <functional>
#include <string_view>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/timer.h"

using ResizeCallback = std::function<void(const int, const int)>;

class Window {
public:
    Window(int width, int height, std::string_view title);

    auto Start(const std::function<void(const double delta)>& program) -> void;

    auto on_resize(ResizeCallback callback) { on_resize_ = callback; }
    auto on_resize() { return on_resize_; }

    ~Window();

private:
    GLFWwindow* window_ {nullptr};
    Timer timer_ {};

    ResizeCallback on_resize_;
};