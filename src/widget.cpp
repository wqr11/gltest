#include <QDir>
#include <QProcessEnvironment>
#include <QMouseEvent>
#include <QTimer>

#include "widget.h"

TwglWidget::TwglWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    /**
     * To capture keyboard input
     */
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
}

void TwglWidget::initializeGL()
{
    ds = std::make_unique<Designer>();
    scene = std::make_unique<Scene>();
    scene->root = std::make_unique<Cube>(ds.get());
    scene->upload();
}

void TwglWidget::resizeGL(int w, int h)
{
    ds->glViewport(0, 0, w, h);
}

void TwglWidget::paintGL()
{
    /**
     * Clear the screen
     */
    ds->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (scene)
        scene->draw();
}

void TwglWidget::mousePressEvent(QMouseEvent *event)
{
    mousePressed = true;
}

void TwglWidget::mouseReleaseEvent(QMouseEvent *event)
{
    mousePressed = false;
}

void TwglWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!mousePressed || !ds || !ds->camera)
        return;

    float sensitivity = 0.01f;
    float deltaTheta = 0;
    float deltaPhi = 0;
    QPoint delta;

    switch (ds->camera->camera_mode)
    {
    case CameraMode::ORBIT:
        delta = event->pos() - lastMousePos;
        lastMousePos = event->pos();

        if (delta.manhattanLength() > stepPx)
            return;

        deltaTheta = delta.x() * sensitivity;
        deltaPhi = delta.y() * sensitivity;

        ds->camera->deltaOrbit(deltaTheta, deltaPhi);

        update();
        break;

    case CameraMode::ORTHO:
        break;
    }
}

void TwglWidget::wheelEvent(QWheelEvent *event)
{

    float scaleFactor = 1.0f + (event->angleDelta().y() / 120.0f) * 0.1f;

    ds->camera->deltaScale(scaleFactor);

    update();
}

void TwglWidget::keyPressEvent(QKeyEvent *event)
{

    switch (event->key())
    {
    case Qt::Key_M:
        ds->camera->cycleCamera();
        break;
    }

    update();
}