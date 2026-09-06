#pragma once

#include <memory>
#include "./geometry/Object.h"
#include "./geometry/Cube.h"

class Scene
{
public:
    std::unique_ptr<Object> root;

    void upload()
    {
        root->upload();
    }

    void draw()
    {
        root->draw();
    }
};
