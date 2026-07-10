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

    int m_stepPx = 100;

    QPoint m_lastMousePos;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

public:
    TwglWidget(QWidget *parent = nullptr);

    std::unique_ptr<Scene> m_scene;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    std::unique_ptr<Designer> m_ds;
};
