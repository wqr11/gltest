#include <QtCore/QDir>
#include <QtCore/QProcessEnvironment>
#include <QtCore/QTimer>
#include <QtGui/QMouseEvent>

#include "../Camera.h"
#include "../geometry/Cube.h"

#include "widget.h"

TwglWidget::TwglWidget(QWidget *parent) : QOpenGLWidget(parent) {
  /**
   * To capture keyboard input
   */
  setFocusPolicy(Qt::StrongFocus);
  setMouseTracking(true);
}

void TwglWidget::initializeGL() {
  r = std::make_unique<Renderer>();
  scene = std::make_unique<Scene>(std::make_unique<Cube>(*r));
  scene->upload();
}

void TwglWidget::resizeGL(int w, int h) { r->glViewport(0, 0, w, h); }

void TwglWidget::paintGL() {
  /**
   * Clear the screen
   */
  r->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (scene) {
    scene->draw();
  }
}

void TwglWidget::mousePressEvent(QMouseEvent *event) { mousePressed = true; }

void TwglWidget::mouseReleaseEvent(QMouseEvent *event) {
  mousePressed = false;
  skipped = false;
}

void TwglWidget::mouseMoveEvent(QMouseEvent *event) {
  if (!mousePressed || !r || !r->camera)
    return;

  float sensitivity = 0.01f;
  float deltaTheta = 0;
  float deltaPhi = 0;
  QPoint delta;

  switch (r->camera->camera_mode) {
  case Camera::Mode::ORBIT:
    delta = event->pos() - lastMousePos;
    lastMousePos = event->pos();

    if (!skipped) {
      skipped = true;
      return;
    }

    deltaTheta = delta.x() * sensitivity;
    deltaPhi = delta.y() * sensitivity;

    r->camera->deltaOrbit(deltaTheta, deltaPhi);

    update();
    break;

  case Camera::Mode::ORTHO:
    break;
  }
}

void TwglWidget::wheelEvent(QWheelEvent *event) {

  float scaleFactor = 1.0f + (event->angleDelta().y() / 120.0f) * 0.1f;

  r->camera->deltaScale(scaleFactor);

  update();
}

void TwglWidget::keyPressEvent(QKeyEvent *event) {

  switch (event->key()) {
  case Qt::Key_M:
    r->camera->cycleCamera();
    break;
  }

  update();
}
