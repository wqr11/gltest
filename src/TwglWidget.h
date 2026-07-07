#pragma once

#ifndef TWGLWIDGET_H
#define TWGLWIDGET_H

#include <QUrl>
#include <QFile>
#include <QOpenGLWidget>
#include <QObject>
#include <QOpenGLFunctions>
#include <memory>

class TwglWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    TwglWidget(QWidget *parent = nullptr);

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    GLuint m_vao = 0;
    GLuint m_vbo = 0;
    GLuint m_shaderProgram = 0;
    GLuint m_vertexShader = 0;
    GLuint m_fragmentShader = 0;

    std::unique_ptr<QString> loadShaderForUrl(QString url);
};

struct ShaderWithSize
{
    const char *src;
    const GLint size;
};

#endif /* TWGLWIDGET_H */