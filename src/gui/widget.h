#pragma once

#include "../Renderer.h"
#include "../Scene.h"
#include <QtOpenGLWidgets/QtOpenGLWidgets>

class TwglWidget : public QOpenGLWidget {
  Q_OBJECT

protected:
  QPoint lastMousePos;
  int arrows[4]{0};
  int stepPx = 10;

  bool mousePressed = false;
  bool skipped = false;

  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;

public:
  TwglWidget(QWidget *parent = nullptr);

  std::unique_ptr<Scene> scene;
  std::unique_ptr<Renderer> r;

  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
};
