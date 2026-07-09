#include <QDir>
#include <QProcessEnvironment>

#include "TwglWidget.h"

TwglWidget::TwglWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    /**
     * To capture keyboard input
     */
    setFocusPolicy(Qt::StrongFocus);
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