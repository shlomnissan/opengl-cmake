// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "texture2d.h"

#include <glad/glad.h>

Texture2D::Texture2D(std::shared_ptr<Image> image) {
    SetTexture(image);
}

auto Texture2D::SetTexture(std::shared_ptr<Image> image) -> void {
    glGenTextures(1, &texture_id_);
    glBindTexture(GL_TEXTURE_2D, texture_id_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        image->width,
        image->height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        image->Data()
    );
    is_loaded_ = true;
}

auto Texture2D::Bind() const -> void {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id_);
}

Texture2D::~Texture2D() {
    glDeleteTextures(1, &texture_id_);
    texture_id_ = 0;
}