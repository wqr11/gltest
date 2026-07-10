#pragma once

#include <memory>
#include "Object.h"
#include "Cube.h"

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
