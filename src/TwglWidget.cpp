#include "TwglWidget.h"
#include <time.h>

std::unique_ptr<QString> TwglWidget::loadShaderForUrl(QString url)
{
    QFile shaderFile(url);

    if (!shaderFile.open(QIODevice::ReadOnly))
    {
        qWarning() << "Failed to open shader for url: " << url;

        throw -1;
    }

    auto shader = std::make_unique<QString>(shaderFile.readAll());

    shaderFile.close();

    return shader;
}

TwglWidget::TwglWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    /**
     * To capture keyboard input
     */
    setFocusPolicy(Qt::StrongFocus);
}

void TwglWidget::initializeGL()
{
    initializeOpenGLFunctions();

    srand(0);
    /**
     * Set default (on-reset) background color
     */
    glClearColor((rand() % 100) / 100, 0, 0, 1);

    /**
     * Enable depth test with depth buffer
     */
    glEnable(GL_DEPTH_TEST);

    const float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f};

    /**
     * Generate buffers & bind VBO
     */
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /**
     * Create program, shaders and attach them
     */
    m_shaderProgram = glCreateProgram();
    m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
    m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    auto vertexShaderSource = loadShaderForUrl(QString("./shaders/vertex.glsl"));
    auto vertexShaderStr = vertexShaderSource->toStdString();
    auto vertexShaderCStr = vertexShaderStr.c_str();
    auto vertexShaderSize = (GLint)vertexShaderSource->size();
    glShaderSource(m_vertexShader, 1, &vertexShaderCStr, &vertexShaderSize);

    auto fragmentShaderSource = loadShaderForUrl(QString("./shaders/fragment.glsl"));
    auto fragmentShaderStr = fragmentShaderSource->toStdString();
    auto fragmentShaderCStr = fragmentShaderStr.c_str();
    auto fragmentShaderSize = (GLint)fragmentShaderSource->size();
    glShaderSource(m_fragmentShader, 1, &fragmentShaderCStr, &fragmentShaderSize);

    glCompileShader(m_vertexShader);
    glCompileShader(m_fragmentShader);

    glAttachShader(m_shaderProgram, m_vertexShader);
    glAttachShader(m_shaderProgram, m_fragmentShader);

    /**
     * Link and use the program
     */
    glLinkProgram(m_shaderProgram);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, nullptr);
    glEnableVertexAttribArray(0);

    glUseProgram(m_shaderProgram);

    /**
     * Program is now linked, we do not need separate shaders now
     */
    glDeleteShader(m_vertexShader);
    glDeleteShader(m_fragmentShader);

    qDebug()
        << "OpenGL initialized!";
}

void TwglWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void TwglWidget::paintGL()
{
    /**
     * Clear the screen
     */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}