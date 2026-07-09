#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/trigonometric.hpp>
#include <glm/ext.hpp>

class Camera
{

public:
    Camera() : up(glm::vec3(0.0f, 1.0f, 0.0f)),
               viewMatrix(glm::lookAt(
                   glm::vec3(0.0f, 0.0f, 1.0f), // Position
                   glm::vec3(0.0f, 0.0f, 0.0f), // Target
                   glm::vec3(0.0f, 1.0f, 0.0f)  // Up
                   )),
               perspectiveMatrix(
                   glm::perspective(
                       glm::radians(60.0f), // FOV
                       16.0f / 9.0f,        // Aspect ratio
                       0.1f,                // Near plane,
                       100.0f               // Far plane
                       ))
    {
    }

    glm::vec3 up;
    glm::mat4 viewMatrix;
    glm::mat4 perspectiveMatrix;
};