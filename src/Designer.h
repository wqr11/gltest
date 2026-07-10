#pragma once

#include <QString>
#include <QOpenGLExtraFunctions>
#include <memory>

#include "Camera.h"

class Designer : public QOpenGLExtraFunctions
{
public:
    Designer();
    ~Designer();

    std::unique_ptr<Camera> m_camera = std::make_unique<Camera>();

    /**
     * Shader program (id)
     */
    GLuint m_shaderProgram = 0;
    /**
     * Shaders (ids)
     */
    GLuint m_vertexShader = 0;
    GLuint m_fragmentShader = 0;
};

struct ShaderWithSize
{
    const char *src;
    const GLint size;
};