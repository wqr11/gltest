#pragma once

#include "./geometry/Object.h"
#include <memory>

class Scene {
public:
  std::unique_ptr<Object> root;

  explicit Scene(std::unique_ptr<Object>);
  void upload();
  void draw();
};
