#include <QFile>
#include <QMessageBox>
#include <QProcessEnvironment>
#include <QDir>
#include "Designer.h"
#include "Cube.h"

Designer::~Designer()
{
    glDeleteProgram(m_shaderProgram);
}

std::unique_ptr<QString> Designer::loadShaderForUrl(QString url)
{
    QFile shaderFile(url);

    if (!shaderFile.open(QIODevice::ReadOnly))
    {
        qWarning() << "Failed to open shader for url: " << url;

        QString title("Error");
        QString text("Shader for url " + url + " was NOT found");
        QMessageBox::critical(nullptr, title, text);

        throw -1;
    }

    auto shader = std::make_unique<QString>(shaderFile.readAll());

    shaderFile.close();

    return shader;
}

Designer::Designer()
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
    m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    auto vertexShaderSource = loadShaderForUrl(QDir().absoluteFilePath(env.value("TWGL_VERTEX_SHADER", "C:/Users/wqr/Desktop/gltest/shaders/vertex.glsl")));
    auto vertexShaderStr = vertexShaderSource->toStdString();
    auto vertexShaderCStr = vertexShaderStr.c_str();
    auto vertexShaderSize = (GLint)vertexShaderSource->size();
    glShaderSource(m_vertexShader, 1, &vertexShaderCStr, &vertexShaderSize);

    auto fragmentShaderSource = loadShaderForUrl(QDir().absoluteFilePath(env.value("TWGL_FRAGMENT_SHADER", "C:/Users/wqr/Desktop/gltest/shaders/fragment.glsl")));
    auto fragmentShaderStr = fragmentShaderSource->toStdString();
    auto fragmentShaderCStr = fragmentShaderStr.c_str();
    auto fragmentShaderSize = (GLint)fragmentShaderSource->size();
    glShaderSource(m_fragmentShader, 1, &fragmentShaderCStr, &fragmentShaderSize);

    glCompileShader(m_vertexShader);
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
        QString text("[[ OPENGL LOGS ]]" + QString(infoLog));
        QMessageBox::critical(nullptr, title, text);
        throw std::runtime_error("Vertex shader error");
    }

    /**
     * 2) Check FRAGMENT_SHADER compile errors
     */
    glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(m_fragmentShader, 512, nullptr, infoLog);
        QString title("FRAGMENT SHADER COMPILATION ERROR");
        QString text("[[ OPENGL LOGS ]]" + QString(infoLog));
        QMessageBox::critical(nullptr, title, text);
        throw std::runtime_error("Vertex shader error");
    }

    glAttachShader(m_shaderProgram, m_vertexShader);
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
        QString title("PROGRAM LIKNING ERROR");
        QString text("[[ OPENGL LOGS ]]" + QString(infoLog));
        QMessageBox::critical(nullptr, title, text);
        throw std::runtime_error("[OPENGL] Program link error");
    }
    // END

    glUseProgram(m_shaderProgram);

    /**
     * Program is now linked, we do not need separate shaders now
     */
    // glDeleteShader(m_vertexShader);
    // glDeleteShader(m_fragmentShader);

    qDebug()
        << "[APPLICATION] OpenGL initialized!";
}
