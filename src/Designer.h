#pragma once

#include <QOpenGLExtraFunctions>
#include <QMessageBox>
#include <memory>
#include "Camera.h"
#include "Shaders.h"

class Designer : public QOpenGLExtraFunctions
{
public:
    std::unique_ptr<Camera> camera = std::make_unique<Camera>();

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

    ~Designer()
    {
        glDeleteProgram(shaderProgram);
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
        shaderProgram = glCreateProgram();
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        const char *p_VERTEX_SHADER_SOURCE = const_cast<const char *>(VERTEX_SHADER_SOURCE);
        const char *p_GEOMETRY_SHADER_SOURCE = const_cast<const char *>(GEOMETRY_SHADER_SOURCE);
        const char *p_FRAGMENT_SHADER_SOURCE = const_cast<const char *>(FRAGMENT_SHADER_SOURCE);

        glShaderSource(vertexShader, 1, &p_VERTEX_SHADER_SOURCE, const_cast<int32_t *>(&VERTEX_SHADER_SIZE));
        glShaderSource(geometryShader, 1, &p_GEOMETRY_SHADER_SOURCE, const_cast<int32_t *>(&GEOMETRY_SHADER_SIZE));
        glShaderSource(fragmentShader, 1, &p_FRAGMENT_SHADER_SOURCE, const_cast<int32_t *>(&FRAGMENT_SHADER_SIZE));

        glCompileShader(vertexShader);
        glCompileShader(geometryShader);
        glCompileShader(fragmentShader);

        /**
         * 1) Check VERTEX_SHADER compile errors
         */
        GLint success;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
            QString title("VERTEX SHADER COMPILATION ERROR");
            QString text("[[ OPENGL LOGS ]] " + QString(infoLog));
            QMessageBox::critical(nullptr, title, text);
            throw std::runtime_error("Vertex shader error");
        }

        /**
         * 2) Check GEOMETRY_SHADER compile errors
         */
        glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
            QString title("GEOMETRY SHADER COMPILATION ERROR");
            QString text("[[ OPENGL LOGS ]] " + QString(infoLog));
            QMessageBox::critical(nullptr, title, text);
            throw std::runtime_error("Geometry shader error");
        }

        /**
         * 3) Check FRAGMENT_SHADER compile errors
         */
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
            QString title("FRAGMENT SHADER COMPILATION ERROR");
            QString text("[[ OPENGL LOGS ]] " + QString(infoLog));
            QMessageBox::critical(nullptr, title, text);
            throw std::runtime_error("Vertex shader error");
        }

        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, geometryShader);
        glAttachShader(shaderProgram, fragmentShader);

        /**
         * Link and use the program
         */
        glLinkProgram(shaderProgram);

        /**
         * 3) Check PROGRALINK errors
         */
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            QString title("PROGRAM LINKING ERROR");
            QString text("[[ OPENGL LOGS ]]" + QString(infoLog));
            QMessageBox::critical(nullptr, title, text);
            throw std::runtime_error("[OPENGL] Program link error");
        }
        // END

        glUseProgram(shaderProgram);

        /**
         * Program is now linked, we do not need separate shaders now
         */
        glDeleteShader(vertexShader);
        glDeleteShader(geometryShader);
        glDeleteShader(fragmentShader);

        qDebug()
            << "[APPLICATION] OpenGL initialized!";
    }
};
