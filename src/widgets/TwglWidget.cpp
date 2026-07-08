#include "TwglWidget.h"
#include <QDir>
#include <QProcessEnvironment>
#include <QMessageBox>
#include <QPushButton>
#include <QFlag>

TwglWidget::~TwglWidget()
{
    glDeleteProgram(m_shaderProgram);
}

std::unique_ptr<QString> TwglWidget::loadShaderForUrl(QString url)
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

    /**
     * Set default (on-reset) background color
     */
    glClearColor(0, 0, 0, 1);

    /**
     * Enable depth test with depth buffer
     */
    // glEnable(GL_DEPTH_TEST);

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

    glAttachShader(m_shaderProgram, m_vertexShader);
    glAttachShader(m_shaderProgram, m_fragmentShader);

    /**
     * Link and use the program
     */
    glLinkProgram(m_shaderProgram);

    m_testCube = std::make_unique<Cube>();

    m_testCube->upload();

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
    glUseProgram(m_shaderProgram);

    /**
     * Clear the screen
     */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (m_testCube)
        m_testCube->draw();
}