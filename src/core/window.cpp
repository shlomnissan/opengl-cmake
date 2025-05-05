// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "window.h"

#include <format>
#include <iostream>

#include <GLFW/glfw3.h>

constexpr auto callback_error =
[](int error, const char* message) {
    std::cout << std::format("Error ({}): {}\n", error, message);
};

Window::Window(int width, int height, std::string_view title) {
    glfwSetErrorCallback(callback_error);

    if (!glfwInit()) {
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
    #endif

    window_ = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
    if (window_ == nullptr) {
        glfwTerminate();
        return;
    }

     glfwMakeContextCurrent(window_);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        return;
    }

    glfwSwapInterval(1);
    glfwSetWindowUserPointer(window_, this);

    auto buffer_width {0}, buffer_height {0};
    glfwGetFramebufferSize(window_, &buffer_width, &buffer_height);
    glViewport(0, 0, buffer_width, buffer_height);
}

auto Window::Start(const std::function<void(const double delta)> &program) -> void {
    timer_.Reset();

    while(!glfwWindowShouldClose(window_)) {
        auto delta = timer_.GetSeconds();
        timer_.Reset();

        program(delta);

        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
}

Window::~Window() {
    glfwDestroyWindow(window_);
    glfwTerminate();
}