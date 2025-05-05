// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "core/geometry.h"

#include <vector>

#include "glm/vec3.hpp"

class BoxGeometry : public Geometry {
public:
    struct Parameters {
        float width;
        float height;
        float depth;
        unsigned width_segments;
        unsigned height_segments;
        unsigned depth_segments;
    };

    explicit BoxGeometry(const Parameters& params);

private:
    struct PlaneParameters {
        char u;
        char v;
        char w;
        int udir;
        int vdir;
        float width;
        float height;
        float depth;
        unsigned grid_x;
        unsigned grid_y;
    };

    unsigned vertex_counter_ {0};

    auto BuildPlane(
        const PlaneParameters& params,
        std::vector<float>& vertex_data,
        std::vector<unsigned int>& index_data
    ) -> void;

    auto SetComponent(glm::vec3& vec, char axis, float value) -> void;
};