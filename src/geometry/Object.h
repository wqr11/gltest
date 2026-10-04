#pragma once

#include "../Designer.h"
#include "Mesh.h"
#include "Texture.h"
#include <cstring>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <vector>

class MeshDrawCommand {
public:
  MeshDrawCommand(GLuint __indexOffset, GLuint __indexCount)
      : indexOffset(__indexOffset), indexCount(__indexCount) {}
  GLuint indexOffset;
  GLuint indexCount;
};

class Object {
protected:
  GLuint vao; // Vertex Array Object (settings)
  GLuint vbo; // Vertex Buffer Object
  GLuint ibo; // Index Buffer Object
  Designer &ds;
  std::vector<MeshDrawCommand> mesh_cmds;
  std::vector<Mesh> meshes;
  std::shared_ptr<Texture> texture;
  // std::vector<Object> children;

public:
  Object(Designer &__ds, std::shared_ptr<Texture> __texture)
      : ds(__ds), texture(__texture) {};

  glm::mat4 modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));

  /**
   * @TODO: Rewrite for glMultiDrawElementsIndirect
   */
  void upload(bool isStatic = false) {
    if (meshes.empty()
        //  && children.empty()
    )
      return;

    GLuint current_vertices = 0;
    GLuint current_indices = 0;

    std::vector<Vertex> merged_vertices;
    std::vector<GLuint> merged_indices;

    /**
     * Reserve space for vectors' data on the heap
     */
    mesh_cmds.reserve(meshes.size());

    // Loop #2 - Maybe fix this
    for (const auto &mesh : meshes) {
      mesh_cmds.emplace_back(current_indices,
                             static_cast<GLuint>(mesh.indices.size()));

      for (const auto &mesh_vert : mesh.vertices) {
        merged_vertices.push_back(mesh_vert);
      }

      for (const auto &mesh_idx : mesh.indices) {
        merged_indices.push_back(mesh_idx + current_vertices);
      }

      current_vertices += mesh.vertices.size();
      current_indices += mesh.indices.size();
    }

    /**
     * Upload data on the GPU (once!)
     */
    ds.glGenVertexArrays(1, &vao);
    ds.glGenBuffers(1, &vbo);
    ds.glGenBuffers(1, &ibo);

    ds.glBindVertexArray(vao);

    /**
     * Upload data to ARRAY_BUFFER
     */
    ds.glBindBuffer(GL_ARRAY_BUFFER, vbo);
    ds.glBufferData(GL_ARRAY_BUFFER, merged_vertices.size() * sizeof(Vertex),
                    merged_vertices.data(),
                    isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);

    /**
     * Upload data to ELEMENT_ARRAY_BUFFER
     */
    ds.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    ds.glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, merged_indices.size() * sizeof(uint32_t),
        merged_indices.data(), isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);

    /**
     * Enable in's
     */
    ds.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                             (void *)offsetof(Vertex, position));

    ds.glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                             (void *)offsetof(Vertex, texCoords));

    ds.glEnableVertexAttribArray(0);
    ds.glBindVertexArray(0);

    /**
     * Cleanup unused meshes
     */
    meshes.clear();
    meshes.shrink_to_fit();

    texture->load();
  }

  void draw() {

    ds.glUseProgram(ds.shaderProgram);

    ds.glBindVertexArray(vao);

    /**
     * Enable uniforms
     */
    ds.glActiveTexture(GL_TEXTURE0);
    texture->glTexture->bind();

    ds.glUniformMatrix4fv(
        ds.glGetUniformLocation(ds.shaderProgram, "modelMatrix"), 1, GL_FALSE,
        glm::value_ptr(modelMatrix));

    ds.glUniformMatrix4fv(
        ds.glGetUniformLocation(ds.shaderProgram, "viewMatrix"), 1, GL_FALSE,
        glm::value_ptr(ds.camera->viewMatrix));

    ds.glUniformMatrix4fv(
        ds.glGetUniformLocation(ds.shaderProgram, "projectionMatrix"), 1,
        GL_FALSE, glm::value_ptr(ds.camera->projectionMatrix));

    ds.glUniform1i(ds.glGetUniformLocation(ds.shaderProgram, "fTexture"), 0);

    // ds.glTex

    for (auto &cmd : mesh_cmds) {
      uintptr_t p_indices =
          static_cast<uintptr_t>(cmd.indexOffset * sizeof(GLuint));
      ds.glDrawElements(GL_TRIANGLES, cmd.indexCount, GL_UNSIGNED_INT,
                        reinterpret_cast<void *>(p_indices));
    }

    ds.glBindVertexArray(0);
  }
};
