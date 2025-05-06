// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "window.h"

#include <format>
#include <iostream>

#include <GLFW/glfw3.h>

#include "events.h"
#include "event_dispatcher.h"

static auto glfw_mouse_button_map(int button) -> MouseButton;
static auto glfw_cursor_pos_callback(GLFWwindow*, double x, double y) -> void;
static auto glfw_mouse_button_callback(GLFWwindow*, int button, int action, int mods) -> void;
static auto glfw_scroll_callback(GLFWwindow*, double x, double y) -> void;

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
    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);
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

    glfwSwapInterval(0); // disable vsync
    glfwSetWindowUserPointer(window_, this);
    glfwSetCursorPosCallback(window_, glfw_cursor_pos_callback);
    glfwSetMouseButtonCallback(window_, glfw_mouse_button_callback);
    glfwSetScrollCallback(window_, glfw_scroll_callback);

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

static auto glfw_cursor_pos_callback(GLFWwindow* _, double x, double y) -> void {
    auto event = std::make_unique<MouseEvent>();
    event->type = MouseEvent::Type::Moved;
    event->button = MouseButton::None;
    event->position = {static_cast<float>(x), static_cast<float>(y)};
    event->scroll = {0.0f, 0.0f};

    EventDispatcher::Get().Dispatch("mouse_event", std::move(event));
}

static auto glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int) -> void {
    auto event = std::make_unique<MouseEvent>();

    event->type = MouseEvent::Type::ButtonPressed;
    event->button = glfw_mouse_button_map(button);
    event->scroll = {0.0f, 0.0f};

    if (action == GLFW_PRESS) {
        EventDispatcher::Get().Dispatch("mouse_event", std::move(event));
    }

    if (action == GLFW_RELEASE) {
        event->type = MouseEvent::Type::ButtonReleased;
        EventDispatcher::Get().Dispatch("mouse_event", std::move(event));
    }
}

static auto glfw_scroll_callback(GLFWwindow* window, double x, double y) -> void {
    auto event = std::make_unique<MouseEvent>();

    event->type = MouseEvent::Type::Scrolled;
    event->button = MouseButton::None;
    event->scroll = {static_cast<float>(x), static_cast<float>(y)};

    EventDispatcher::Get().Dispatch("mouse_event", std::move(event));
}

static auto glfw_mouse_button_map(int button) -> MouseButton {
    switch(button) {
        case GLFW_MOUSE_BUTTON_LEFT: return MouseButton::Left;
        case GLFW_MOUSE_BUTTON_RIGHT: return MouseButton::Right;
        case GLFW_MOUSE_BUTTON_MIDDLE: return MouseButton::Middle;
        default: break;
    }
    return MouseButton::None;
}