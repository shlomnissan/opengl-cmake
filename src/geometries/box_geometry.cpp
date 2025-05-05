// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "box_geometry.h"

#include <vector>

BoxGeometry::BoxGeometry(const Parameters& params) {
    auto vertex_data = std::vector<float>();
    auto index_data = std::vector<unsigned int>();

    BuildPlane({
        'z', 'y', 'x', -1, -1,
        params.depth, params.height, params.width,
        params.depth_segments, params.height_segments
    }, vertex_data, index_data);

    BuildPlane({
        'z', 'y', 'x', 1, -1,
        params.depth, params.height, -params.width,
        params.depth_segments, params.height_segments
    }, vertex_data, index_data);

    BuildPlane({
        'x', 'z', 'y', 1, 1,
        params.width, params.depth, params.height,
        params.width_segments, params.depth_segments
    }, vertex_data, index_data);

    BuildPlane({
        'x', 'z', 'y', 1, -1,
        params.width, params.depth, -params.height,
        params.width_segments, params.depth_segments
    }, vertex_data, index_data);

    BuildPlane({
        'x', 'y', 'z', 1, -1,
        params.width, params.height, params.depth,
        params.width_segments, params.height_segments
    }, vertex_data, index_data);

    BuildPlane({
        'x', 'y', 'z', -1, -1,
        params.width, params.height, -params.depth,
        params.width_segments, params.height_segments
    }, vertex_data, index_data);

    SetVertexData(vertex_data, index_data);
}

auto BoxGeometry::BuildPlane(
    const PlaneParameters& params,
    std::vector<float>& vertex_data,
    std::vector<unsigned int>& index_data
) -> void {
    const auto width_half = params.width / 2;
    const auto height_half = params.height / 2;
    const auto depth_half = params.depth / 2;

    const auto grid_x1 = params.grid_x + 1;
    const auto grid_y1 = params.grid_y + 1;

    const auto segment_w = params.width / params.grid_x;
    const auto segment_h = params.height / params.grid_y;

    auto vec = glm::vec3 {};
    auto counter = 0;

    for (auto iy = 0; iy < grid_y1; ++iy) {
        const auto y = iy * segment_h - height_half;
        for (auto ix = 0; ix < grid_x1; ++ix) {
            const auto x = ix * segment_w - width_half;

            // set position
            SetComponent(vec, params.u, x * params.udir);
            SetComponent(vec, params.v, y * params.vdir);
            SetComponent(vec, params.w, depth_half);

            vertex_data.emplace_back(vec.x);  // pos x
            vertex_data.emplace_back(vec.y);  // pos y
            vertex_data.emplace_back(vec.z);  // pos z

            // set normals
            SetComponent(vec, params.u, 0);
            SetComponent(vec, params.v, 0);
            SetComponent(vec, params.w, params.depth > 0 ? 1 : -1);

            vertex_data.emplace_back(vec.x);  // normal x
            vertex_data.emplace_back(vec.y);  // normal y
            vertex_data.emplace_back(vec.z);  // normal z

            // set uvs
            const auto u = static_cast<float>(ix) / params.grid_x;
            const auto v = 1 - (static_cast<float>(iy) / params.grid_y);
            vertex_data.emplace_back(u);
            vertex_data.emplace_back(v);

            ++counter;
        }
    }

    for (auto iy = 0; iy < params.grid_y; ++iy) {
        for (auto ix = 0; ix < params.grid_x; ++ix) {
            const auto a = vertex_counter_ + ix + grid_x1 * iy;
            const auto b = vertex_counter_ + ix + grid_x1 * (iy + 1);
            const auto c = vertex_counter_ + ix + 1 + grid_x1 * (iy + 1);
            const auto d = vertex_counter_ + ix + 1 + grid_x1 * iy;

            index_data.emplace_back(a);
            index_data.emplace_back(b);
            index_data.emplace_back(d);
            index_data.emplace_back(b);
            index_data.emplace_back(c);
            index_data.emplace_back(d);
        }
    }

    vertex_counter_ += counter;
}

auto BoxGeometry::SetComponent(glm::vec3& vec, char axis, float value) -> void {
    switch(axis) {
        case 'x': vec.x = value; break;
        case 'y': vec.y = value; break;
        case 'z': vec.z = value; break;
    }
}