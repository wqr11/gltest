#include "Camera.h"

Camera::Camera() {
  this->__orbitViewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f), // Position
                                        target,                      // Target
                                        up                           // Up
  );

  this->__orbitPerspectiveMatrix =
      glm::perspective(glm::radians(60.0f), // FOV
                       16.0f / 9.0f,        // Aspect ratio
                       0.1f,                // Near plane,
                       100.0f               // Far plane
      );

  this->viewMatrix = this->__orbitViewMatrix;
  this->projectionMatrix = this->__orbitPerspectiveMatrix;
};

void Camera::cycleCamera() {
  switch (camera_mode) {
  case Mode::ORBIT:
    this->applyOrtho();
    break;
  case Mode::ORTHO:
    this->applyOrbit();
    break;
  }
};

void Camera::applyOrtho() {
  camera_mode = Mode::ORTHO;
  viewMatrix =
      glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), up);
}

void Camera::applyOrbit() {
  if (camera_mode != Mode::ORBIT)
    projectionMatrix = __orbitPerspectiveMatrix;

  camera_mode = Mode::ORBIT;

  glm::vec3 pos;

  pos.x = target.x + radius * sin(theta) * cos(phi);
  pos.y = target.y + radius * sin(phi);
  pos.z = target.z + radius * cos(theta) * cos(phi);

  viewMatrix = glm::lookAt(pos, target, up);
}

void Camera::deltaOrbit(float dt, float dp) {
  theta -= dt;
  phi = glm::clamp(phi + dp, 0.1f, glm::radians(89.0f));

  this->applyOrbit();
}

void Camera::deltaScale(float ds) {
  fov = glm::clamp(fov * ds, 1.0f, 160.0f);

  projectionMatrix = glm::perspective(glm::radians(fov), // FOV
                                      16.0f / 9.0f,      // Aspect ratio
                                      0.1f,              // Near plane,
                                      100.0f             // Far plane
  );
}
