#pragma once

#include <QtCore/QObject>
#include <QtOpenGLWidgets/QtOpenGLWidgets>
#include <memory>

#include "../Camera.h"
#include "../Designer.h"
#include "../Scene.h"

class TwglWidget : public QOpenGLWidget {
  Q_OBJECT

protected:
  bool mousePressed = false;

  int stepPx = 10;

  QPoint lastMousePos;

  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;

public:
  TwglWidget(QWidget *parent = nullptr);

  std::unique_ptr<Scene> scene;
  std::unique_ptr<Designer> ds;

  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
};
