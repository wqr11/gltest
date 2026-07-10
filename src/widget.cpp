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
    m_ds = std::make_unique<Designer>();
    m_scene = std::make_unique<Scene>();
    m_scene->m_root = std::make_unique<Cube>(m_ds.get());
    m_scene->upload();
}

void TwglWidget::resizeGL(int w, int h)
{
    m_ds->glViewport(0, 0, w, h);
}

void TwglWidget::paintGL()
{
    /**
     * Clear the screen
     */
    m_ds->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (m_scene)
        m_scene->draw();
}

void TwglWidget::mousePressEvent(QMouseEvent *event)
{
    m_mousePressed = true;
}

void TwglWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_mousePressed = false;
}

void TwglWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_mousePressed || !m_ds || !m_ds->m_camera)
        return;

    float sensitivity = 0.01f;
    float deltaTheta = 0;
    float deltaPhi = 0;
    QPoint delta;

    switch (m_ds->m_camera->m_camera_mode)
    {
    case CameraMode::ORBIT:
        delta = event->pos() - m_lastMousePos;
        m_lastMousePos = event->pos();

        if (delta.manhattanLength() > m_stepPx)
            return;

        deltaTheta = delta.x() * sensitivity;
        deltaPhi = delta.y() * sensitivity;

        m_ds->m_camera->deltaOrbit(deltaTheta, deltaPhi);

        update();
        break;

    case CameraMode::ORTHO:
        break;
    }
}

void TwglWidget::wheelEvent(QWheelEvent *event)
{

    float scaleFactor = 1.0f + (event->angleDelta().y() / 120.0f) * 0.1f;

    m_ds->m_camera->deltaScale(scaleFactor);

    update();
}

void TwglWidget::keyPressEvent(QKeyEvent *event)
{

    switch (event->key())
    {
    case Qt::Key_M:
        m_ds->m_camera->cycleCamera();
        break;
    }

    update();
}