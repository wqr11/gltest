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
    float m_radius = 1.0f;
    float m_scale = 1.0f;
    float m_fov = 60.0f;
    float m_theta = 0.0f;              // Horizontal angle (radians)
    float m_phi = glm::radians(30.0f); // Vertical angle (radians)
    glm::vec3 m_target = glm::vec3(0.0f);

    const glm::mat4 __orbitPerspectiveMatrix = glm::perspective(
        glm::radians(60.0f), // FOV
        16.0f / 9.0f,        // Aspect ratio
        0.1f,                // Near plane,
        100.0f               // Far plane
    );

    const glm::mat4 __orbitViewMatrix = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 1.0f), // Position
        m_target,                    // Target
        m_up                         // Up
    );

public:
    Camera() : m_up(glm::vec3(0.0f, 1.0f, 0.0f)),
               m_viewMatrix(__orbitViewMatrix),
               m_projectionMatrix(__orbitPerspectiveMatrix)
    {
    }

    CameraMode m_camera_mode = CameraMode::ORBIT;

    glm::vec3 m_up;
    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;

    void cycleCamera()
    {
        switch (m_camera_mode)
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
        m_camera_mode = CameraMode::ORTHO;

        m_viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), m_up);
    }

    void applyOrbit()
    {
        if (m_camera_mode != CameraMode::ORBIT)
            m_projectionMatrix = __orbitPerspectiveMatrix;

        m_camera_mode = CameraMode::ORBIT;

        glm::vec3 pos;

        pos.x = m_target.x + m_radius * sin(m_theta) * cos(m_phi);
        pos.y = m_target.y + m_radius * sin(m_phi);
        pos.z = m_target.z + m_radius * cos(m_theta) * cos(m_phi);

        m_viewMatrix = glm::lookAt(pos, m_target, m_up);
    }

    void deltaOrbit(float dt, float dp)
    {
        m_theta -= dt;
        m_phi = glm::clamp(m_phi + dp, 0.1f, glm::radians(89.0f));

        this->applyOrbit();
    }

    void deltaScale(float ds)
    {
        m_fov = glm::clamp(m_fov * ds, 1.0f, 160.0f);

        m_projectionMatrix =
            glm::perspective(
                glm::radians(m_fov), // FOV
                16.0f / 9.0f,        // Aspect ratio
                0.1f,                // Near plane,
                100.0f               // Far plane
            );
    }
};