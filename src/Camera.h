#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/trigonometric.hpp>
#include <glm/ext.hpp>

class Camera
{
private:
    float m_radius = 1.0f;
    float m_scale = 1.0f;
    float m_fov = 60.0f;
    float m_theta = 0.0f;              // Horizontal angle (radians)
    float m_phi = glm::radians(30.0f); // Vertical angle (radians)
    glm::vec3 m_target = glm::vec3(0.0f);

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

    void applyOrbit()
    {
        glm::vec3 pos;

        pos.x = m_target.x + m_radius * sin(m_theta) * cos(m_phi);
        pos.y = m_target.y + m_radius * sin(m_phi);
        pos.z = m_target.z + m_radius * cos(m_theta) * cos(m_phi);

        viewMatrix = glm::lookAt(pos, m_target, up);
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

        perspectiveMatrix =
            glm::perspective(
                glm::radians(m_fov), // FOV
                16.0f / 9.0f,        // Aspect ratio
                0.1f,                // Near plane,
                100.0f               // Far plane
            );
    }
};