// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "core/image.h"

#include <memory>

class Texture2D {
public:
    Texture2D() = default;

    explicit Texture2D(std::shared_ptr<Image> image);

    auto SetTexture(std::shared_ptr<Image> image) -> void;

    auto Bind() const -> void;

    [[nodiscard]] auto IsLoaded() const -> bool {
        return is_loaded_;
    }

    ~Texture2D();

private:
    unsigned int texture_id_;

    bool is_loaded_ {false};
};