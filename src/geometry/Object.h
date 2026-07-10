#pragma once

#include <vector>
#include <cstring>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Mesh.h"
#include "Designer.h"

class MeshDrawCommand
{
public:
    MeshDrawCommand(GLuint __indexOffset, GLuint __indexCount) : indexOffset(__indexOffset), indexCount(__indexCount) {}
    GLuint indexOffset;
    GLuint indexCount;
};

class Object
{
protected:
    GLuint m_vao; // Vertex Array Object (settings)
    GLuint m_vbo; // Vertex Buffer Object
    GLuint m_ibo; // Index Buffer Object
    Designer *ds = nullptr;
    std::vector<MeshDrawCommand> m_mesh_cmds;
    std::vector<Mesh> meshes;
    std::vector<Object> children;

public:
    Object(Designer *__ds) : ds(__ds) {};

    glm::mat4 modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));

    /**
     * @TODO: Rewrite for glMultiDrawElementsIndirect
     */
    void upload(bool isStatic = false)
    {
        if (meshes.empty() && children.empty())
            return;

        GLuint current_vertices = 0;
        GLuint current_indices = 0;

        std::vector<Vertex> merged_vertices;
        std::vector<GLuint> merged_indices;

        /**
         * Reserve space for vectors' data on the heap
         */
        m_mesh_cmds.reserve(meshes.size());

        // Loop #2 - Maybe fix this
        for (const auto &mesh : meshes)
        {
            m_mesh_cmds.emplace_back(current_indices, static_cast<GLuint>(mesh.indices.size()));

            for (const auto &mesh_vert : mesh.vertices)
            {
                merged_vertices.push_back(mesh_vert);
            }

            for (const auto &mesh_idx : mesh.indices)
            {
                merged_indices.push_back(mesh_idx + current_vertices);
            }

            current_vertices += mesh.vertices.size();
            current_indices += mesh.indices.size();
        }

        /**
         * Upload data on the GPU (once!)
         */
        ds->glGenVertexArrays(1, &m_vao);
        ds->glGenBuffers(1, &m_vbo);
        ds->glGenBuffers(1, &m_ibo);

        ds->glBindVertexArray(m_vao);

        /**
         * Upload data to ARRAY_BUFFER
         */
        ds->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        ds->glBufferData(GL_ARRAY_BUFFER, merged_vertices.size() * sizeof(Vertex), merged_vertices.data(), isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);

        /**
         * Upload data to ELEMENT_ARRAY_BUFFER
         */
        ds->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        ds->glBufferData(GL_ELEMENT_ARRAY_BUFFER, merged_indices.size() * sizeof(uint32_t), merged_indices.data(), isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);

        /**
         * Enable in's
         */
        ds->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
        ds->glEnableVertexAttribArray(0);

        ds->glBindVertexArray(0);

        m_mesh_cmds = std::move(m_mesh_cmds);

        /**
         * Cleanup unused meshes
         */
        meshes.clear();
        meshes.shrink_to_fit();
    }

    void draw()
    {
        ds->glUseProgram(ds->m_shaderProgram);

        ds->glBindVertexArray(m_vao);

        /**
         * Enable uniforms
         */

        ds->glUniformMatrix4fv(ds->glGetUniformLocation(ds->m_shaderProgram, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
        ds->glUniformMatrix4fv(ds->glGetUniformLocation(ds->m_shaderProgram, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(ds->m_camera->m_viewMatrix));
        ds->glUniformMatrix4fv(ds->glGetUniformLocation(ds->m_shaderProgram, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(ds->m_camera->m_projectionMatrix));

        for (auto &cmd : m_mesh_cmds)
        {
            uintptr_t p_indices = static_cast<uintptr_t>(cmd.indexOffset * sizeof(GLuint));
            ds->glDrawElements(GL_TRIANGLES, cmd.indexCount, GL_UNSIGNED_INT, reinterpret_cast<void *>(p_indices));
        }

        ds->glBindVertexArray(0);
    }
};
