#pragma once

#include <glm/vec3.hpp>

using namespace glm;

struct Vertex
{
public:
    Vertex(float x, float y, float z) : position(x, y, z) {};

    /**
     * Usually in range [0, 1] and relative to the parent (Object)
     */
    vec3 position;
};