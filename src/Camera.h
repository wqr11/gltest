#pragma once

#include <glm/ext.hpp>
#include <glm/mat4x4.hpp>
#include <glm/trigonometric.hpp>
#include <glm/vec3.hpp>

class Camera {
private:
  /* ORBIT*/
  float radius = 1.0f;
  float scale = 1.0f;
  float fov = 60.0f;
  float theta = 0.0f;              // Horizontal angle (radians)
  float phi = glm::radians(30.0f); // Vertical angle (radians)
  glm::vec3 target = glm::vec3(0.0f);

  glm::mat4 __orbitPerspectiveMatrix;
  glm::mat4 __orbitViewMatrix;

public:
  enum class Mode : int { ORBIT = 0, ORTHO = 1 };

  Camera::Mode camera_mode = Mode::ORBIT;
  glm::mat4 viewMatrix;
  glm::mat4 projectionMatrix;

  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

  explicit Camera();
  ~Camera() = default;

  void cycleCamera();
  void applyOrtho();
  void applyOrbit();
  void deltaOrbit(float dt, float dp);
  void deltaScale(float ds);
};
