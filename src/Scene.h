#pragma once

#include <memory>
#include "Object.h"
#include "Cube.h"

class Scene
{
public:
    std::unique_ptr<Object> m_root;

    void upload()
    {
        m_root->upload();
    }

    void draw()
    {
        m_root->draw();
    }
};
