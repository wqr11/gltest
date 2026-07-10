#pragma once

#include <memory>
#include "Texture.h"

class Material
{
    std::shared_ptr<Texture> diffuseMap;
};