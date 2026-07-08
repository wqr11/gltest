#pragma once

#ifndef TWGLWIDGET_H
#define TWGLWIDGET_H

#include <QUrl>
#include <QFile>
#include <QOpenGLWidget>
#include <QObject>
#include <QOpenGLFunctions>
#include <memory>

#include "Cube.h"

class TwglWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    TwglWidget(QWidget *parent = nullptr);

    ~TwglWidget();

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    std::unique_ptr<Cube> m_testCube;

    /**
     * Shader program (id)
     */
    GLuint m_shaderProgram = 0;
    /**
     * Shaders (ids)
     */
    GLuint m_vertexShader = 0;
    GLuint m_fragmentShader = 0;

    // =============== METHODS ===============

    std::unique_ptr<QString> loadShaderForUrl(QString url);
};

struct ShaderWithSize
{
    const char *src;
    const GLint size;
};

#endif /* TWGLWIDGET_H */