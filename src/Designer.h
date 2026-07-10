#pragma once

#include <QOpenGLExtraFunctions>
#include <QMessageBox>
#include <memory>
#include "Camera.h"
#include "Shaders.h"

class Designer : public QOpenGLExtraFunctions
{
public:
    std::unique_ptr<Camera> m_camera = std::make_unique<Camera>();

    /**
     * Shader program (id)
     */
    GLuint m_shaderProgram = 0;
    /**
     * Shaders (ids)
     */
    GLuint m_vertexShader = 0;
    GLuint m_geometryShader = 0;
    GLuint m_fragmentShader = 0;

    ~Designer()
    {
        glDeleteProgram(m_shaderProgram);
    }

    /**
     * Creates program w/ shaders
     */
    Designer()
    {
        initializeOpenGLFunctions();

        /**
         * Set default (on-reset) background color
         */
        glClearColor(0, 0, 0, 1);

        /**
         * Enable depth test with depth buffer
         */
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        /**
         * Create program, shaders and attach them
         */
        m_shaderProgram = glCreateProgram();
        m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
        m_geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
        m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        const char *p_VERTEX_SHADER_SOURCE = const_cast<const char *>(VERTEX_SHADER_SOURCE);
        const char *p_GEOMETRY_SHADER_SOURCE = const_cast<const char *>(GEOMETRY_SHADER_SOURCE);
        const char *p_FRAGMENT_SHADER_SOURCE = const_cast<const char *>(FRAGMENT_SHADER_SOURCE);

        glShaderSource(m_vertexShader, 1, &p_VERTEX_SHADER_SOURCE, const_cast<int32_t *>(&VERTEX_SHADER_SIZE));
        glShaderSource(m_geometryShader, 1, &p_GEOMETRY_SHADER_SOURCE, const_cast<int32_t *>(&GEOMETRY_SHADER_SIZE));
        glShaderSource(m_fragmentShader, 1, &p_FRAGMENT_SHADER_SOURCE, const_cast<int32_t *>(&FRAGMENT_SHADER_SIZE));

        glCompileShader(m_vertexShader);
        glCompileShader(m_geometryShader);
        glCompileShader(m_fragmentShader);

        /**
         * 1) Check VERTEX_SHADER compile errors
         */
        GLint success;
        glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(m_vertexShader, 512, nullptr, infoLog);
            QString title("VERTEX SHADER COMPILATION ERROR");
            QString text("[[ OPENGL LOGS ]] " + QString(infoLog));
            QMessageBox::critical(nullptr, title, text);
            throw std::runtime_error("Vertex shader error");
        }

        /**
         * 2) Check GEOMETRY_SHADER compile errors
         */
        glGetShaderiv(m_geometryShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(m_fragmentShader, 512, nullptr, infoLog);
            QString title("GEOMETRY SHADER COMPILATION ERROR");
            QString text("[[ OPENGL LOGS ]] " + QString(infoLog));
            QMessageBox::critical(nullptr, title, text);
            throw std::runtime_error("Geometry shader error");
        }

        /**
         * 3) Check FRAGMENT_SHADER compile errors
         */
        glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(m_fragmentShader, 512, nullptr, infoLog);
            QString title("FRAGMENT SHADER COMPILATION ERROR");
            QString text("[[ OPENGL LOGS ]] " + QString(infoLog));
            QMessageBox::critical(nullptr, title, text);
            throw std::runtime_error("Vertex shader error");
        }

        glAttachShader(m_shaderProgram, m_vertexShader);
        glAttachShader(m_shaderProgram, m_geometryShader);
        glAttachShader(m_shaderProgram, m_fragmentShader);

        /**
         * Link and use the program
         */
        glLinkProgram(m_shaderProgram);

        /**
         * 3) Check PROGRAM_LINK errors
         */
        glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetProgramInfoLog(m_shaderProgram, 512, nullptr, infoLog);
            QString title("PROGRAM LINKING ERROR");
            QString text("[[ OPENGL LOGS ]]" + QString(infoLog));
            QMessageBox::critical(nullptr, title, text);
            throw std::runtime_error("[OPENGL] Program link error");
        }
        // END

        glUseProgram(m_shaderProgram);

        /**
         * Program is now linked, we do not need separate shaders now
         */
        glDeleteShader(m_vertexShader);
        glDeleteShader(m_geometryShader);
        glDeleteShader(m_fragmentShader);

        qDebug()
            << "[APPLICATION] OpenGL initialized!";
    }
};
