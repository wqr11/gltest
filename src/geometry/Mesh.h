#include <vector>
#include <QOpenGLExtraFunctions>
#include "Vertex.h"

class Mesh : protected QOpenGLExtraFunctions
{
protected:
    GLuint m_vao = 0; // Vertex Array Object (settings)
    GLuint m_vbo = 0; // Vertex Buffer Object
    GLuint m_ibo = 0; // Index Buffer Object
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

public:
    Mesh()
    {
        initializeOpenGLFunctions();

        glGenBuffers(1, &m_vbo);
        glGenBuffers(1, &m_ibo);
        glGenVertexArrays(1, &m_vao);
    }

    void upload()
    {
        if (vertices.empty() || indices.empty())
            return;

        /**
         * Record attrib settings & ibo in VAO
         */
        glBindVertexArray(m_vao);

        /**
         * Upload data to ARRAY_BUFFER
         */
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        /**
         * Upload data to ELEMENT_ARRAY_BUFFER
         */
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
    }

    void draw()
    {
        if (!m_vao || indices.empty())
            return;

        glBindVertexArray(m_vao);
        glDrawElements(GL_LINE, indices.size(), GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }
};
