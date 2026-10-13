#pragma once

#include "Vertex.h"
#include <vector>

class Mesh {
public:
  Mesh(std::vector<Vertex> __vertices, std::vector<uint32_t> __indices)
      : vertices(__vertices), indices(__indices) {}
  std::vector<Vertex> vertices;
  std::vector<uint32_t> indices;
};
