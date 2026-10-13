#include <QtCore/QDir>
#include <QtCore/QProcessEnvironment>
#include <QtCore/QTimer>
#include <QtGui/QMouseEvent>

#include <cstdlib>

#include "../Camera.h"
#include "../geometry/Cube.h"
#include "glm/matrix.hpp"

#include "widget.h"

using namespace glm;

TwglWidget::TwglWidget(QWidget *parent) : QOpenGLWidget(parent) {
  std::srand(std::time(nullptr));
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

QDebug operator<<(QDebug dbg, const vec4 &v) {
  dbg << "x y z w:" << v.x << v.y << v.z << v.w;
};

void TwglWidget::paintGL() {
  /**
   * Clear the screen
   */
  r->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (scene) {
    scene->draw();
  }
}

void TwglWidget::mousePressEvent(QMouseEvent *event) {
  mousePressed = true;

  int width = window()->width();
  int height = window()->height();

  QPoint p = event->pos();

  float xndc = (float)2 * p.x() / width - 1.0f;
  float yndc = 1.0f - (float)2 * p.y() / height;

  vec4 pndc(xndc, yndc, -1.0f, 1.0f);

  mat4 &view = r->camera->viewMatrix;
  mat4 &projection = r->camera->projectionMatrix;

  mat4 invVp = inverse(projection * view);
  vec4 worldPos4 = invVp * pndc;
  worldPos4 /= worldPos4.w; // perspective divide

  mat4 invView = inverse(view);
  vec4 cameraPos4(invView[3][0], invView[3][1], invView[3][2], 1.0f);

  vec4 dir = worldPos4 - cameraPos4;

  qDebug() << dir;
}

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
  Qt::KeyboardModifiers mods = event->keyCombination().keyboardModifiers();

  int koef = mods.testFlag(Qt::KeyboardModifier::ShiftModifier) ? 5 : 1;

  mat4 &mat = this->scene->root->modelMatrix;

  switch (event->key()) {
  case Qt::Key_M:
    r->camera->cycleCamera();
    break;

  case Qt::Key_Up:
    arrows[0] = 1;
    break;

  case Qt::Key_Down:
    arrows[2] = 1;
    break;

  case Qt::Key_Left:
    arrows[3] = 1;
    break;

  case Qt::Key_Right:
    arrows[1] = 1;
    break;

  default:
    break;
  }

  if (arrows[0]) {
    mat = translate(mat, vec3(0.0f, koef * 0.01f, 0.0f));
  }

  if (arrows[1]) {
    mat = translate(mat, vec3(koef * 0.01f, 0.0f, 0.0f));
  }

  if (arrows[2]) {
    mat = translate(mat, vec3(0.0f, koef * -0.01f, 0.0f));
  }

  if (arrows[3]) {
    mat = translate(mat, vec3(koef * -0.01f, 0.0f, 0.0f));
  }

  update();
}

void TwglWidget::keyReleaseEvent(QKeyEvent *event) {
  switch (event->key()) {

  case Qt::Key_Up:
    arrows[0] = 0;
    break;

  case Qt::Key_Down:
    arrows[2] = 0;
    break;

  case Qt::Key_Left:
    arrows[3] = 0;
    break;

  case Qt::Key_Right:
    arrows[1] = 0;
    break;

  default:
    break;
  }
}
