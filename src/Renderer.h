#pragma once

#include <QtGui/QOpenGLExtraFunctions>
#include <QtWidgets/QMessageBox>
#include <memory>

class Camera;

class Renderer : public QOpenGLExtraFunctions {
public:
  std::unique_ptr<Camera> camera;

  /**
   * Shader program (id)
   */
  GLuint shaderProgram = 0;
  /**
   * Shaders (ids)
   */
  GLuint vertexShader = 0;
  GLuint geometryShader = 0;
  GLuint fragmentShader = 0;

  explicit Renderer();
  ~Renderer();
};
