#pragma once

#include <vector>
#include "Object.h"

class Cube : public Object
{
public:
    Cube(Designer *__ds) : Object(__ds)
    {
        std::vector<Vertex> t_vertices = {
            // Front face (z = -0.5)
            {-0.5f, -0.5f, -0.5f}, // 0
            {-0.5f, 0.5f, -0.5f},  // 1
            {0.5f, 0.5f, -0.5f},   // 2
            {0.5f, -0.5f, -0.5f},  // 3
            // Back face (z = 0.5)
            {-0.5f, -0.5f, 0.5f}, // 4
            {-0.5f, 0.5f, 0.5f},  // 5
            {0.5f, 0.5f, 0.5f},   // 6
            {0.5f, -0.5f, 0.5f}   // 7
        };

        std::vector<uint32_t> t_indices = {
            // Front face
            0, 1, 2,
            0, 2, 3,
            // Back face
            4, 6, 5,
            4, 7, 6,
            // Left face
            0, 4, 5,
            0, 5, 1,
            // Right face
            3, 2, 6,
            3, 6, 7,
            // Bottom face
            0, 3, 7,
            0, 7, 4,
            // Top face
            1, 5, 6,
            1, 6, 2};

        meshes.emplace_back(std::move(t_vertices), std::move(t_indices));
    }
};