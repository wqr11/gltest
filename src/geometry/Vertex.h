#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

using namespace glm;

class Vertex {
public:
  Vertex(float x, float y, float z, float tx, float ty)
      : position(x, y, z), texCoords(tx, ty) {};

  vec2 texCoords;
  /**
   * Usually in range [0, 1] and relative to the parent (Object)
   */
  vec3 position;
};
