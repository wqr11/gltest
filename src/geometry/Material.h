#pragma once

#include <memory>

class Texture;

class Material {
  std::shared_ptr<Texture> diffuseMap;
};
