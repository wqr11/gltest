#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/trigonometric.hpp>
#include <glm/ext.hpp>

enum CameraMode
{
    ORBIT = 0,
    ORTHO = 1
};

class Camera
{
private:
    /* ORBIT*/
    float radius = 1.0f;
    float scale = 1.0f;
    float fov = 60.0f;
    float theta = 0.0f;              // Horizontal angle (radians)
    float phi = glm::radians(30.0f); // Vertical angle (radians)
    glm::vec3 target = glm::vec3(0.0f);

    const glm::mat4 __orbitPerspectiveMatrix = glm::perspective(
        glm::radians(60.0f), // FOV
        16.0f / 9.0f,        // Aspect ratio
        0.1f,                // Near plane,
        100.0f               // Far plane
    );

    const glm::mat4 __orbitViewMatrix = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 1.0f), // Position
        target,                      // Target
        up                           // Up
    );

public:
    Camera() : up(glm::vec3(0.0f, 1.0f, 0.0f)),
               viewMatrix(__orbitViewMatrix),
               projectionMatrix(__orbitPerspectiveMatrix)
    {
    }

    CameraMode camera_mode = CameraMode::ORBIT;

    glm::vec3 up;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    void cycleCamera()
    {
        switch (camera_mode)
        {
        case CameraMode::ORBIT:
            this->applyOrtho();
            break;
        case CameraMode::ORTHO:
            this->applyOrbit();
            break;
        }
    }

    void applyOrtho()
    {
        camera_mode = CameraMode::ORTHO;

        viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), up);
    }

    void applyOrbit()
    {
        if (camera_mode != CameraMode::ORBIT)
            projectionMatrix = __orbitPerspectiveMatrix;

        camera_mode = CameraMode::ORBIT;

        glm::vec3 pos;

        pos.x = target.x + radius * sin(theta) * cos(phi);
        pos.y = target.y + radius * sin(phi);
        pos.z = target.z + radius * cos(theta) * cos(phi);

        viewMatrix = glm::lookAt(pos, target, up);
    }

    void deltaOrbit(float dt, float dp)
    {
        theta -= dt;
        phi = glm::clamp(phi + dp, 0.1f, glm::radians(89.0f));

        this->applyOrbit();
    }

    void deltaScale(float ds)
    {
        fov = glm::clamp(fov * ds, 1.0f, 160.0f);

        projectionMatrix =
            glm::perspective(
                glm::radians(fov), // FOV
                16.0f / 9.0f,      // Aspect ratio
                0.1f,              // Near plane,
                100.0f             // Far plane
            );
    }
};