#pragma once

#include <QOpenGLWidget>
#include <QObject>
#include <memory>

#include "Camera.h"
#include "Scene.h"
#include "Designer.h"

class TwglWidget : public QOpenGLWidget
{
    Q_OBJECT

protected:
    bool m_mousePressed = false;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

public:
    TwglWidget(QWidget *parent = nullptr);

    std::unique_ptr<Scene> m_scene;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    std::unique_ptr<Designer> m_ds;
};
