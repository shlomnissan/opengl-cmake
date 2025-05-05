// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <stdexcept>
#include <string_view>
#include <vector>

#include <glm/glm.hpp>
#include <glad/glad.h>

enum class ShaderType {
    kVertexShader,
    kFragmentShader
};

struct ShaderInfo {
    ShaderType type;
    std::string_view source;
};

class Shaders {
public:
    explicit Shaders(const std::vector<ShaderInfo>& shaders);

    auto Use() const -> void;

    auto GetUniform(std::string_view name) const -> GLint;

    auto SetUniform(std::string_view uniform, int i) const -> void;
    auto SetUniform(std::string_view uniform, const float f) const -> void;
    auto SetUniform(std::string_view uniform, const glm::vec3& vec) const -> void;
    auto SetUniform(std::string_view uniform, const glm::mat3& matrix) const -> void;
    auto SetUniform(std::string_view uniform, const glm::mat4& matrix) const -> void;

    ~Shaders();

private:
    GLuint program_;

    auto CheckProgramLinkStatus() const -> void;
    auto CheckShaderCompileStatus(GLuint shader_id, ShaderType type) const -> void;

    auto GetShaderType(ShaderType type) const -> GLuint;
    auto GetShaderTypeString(ShaderType type) const -> const char*;
};

struct ShaderError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};