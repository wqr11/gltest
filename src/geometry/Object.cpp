#include "Object.h"
#include "../Camera.h"
#include "../Renderer.h"
#include "../geometry/Vertex.h"
#include "Mesh.h"
#include "Texture.h"

void Object::upload(bool isStatic) {
  if (meshes.empty()) {
    return;
  }

  GLuint current_vertices = 0;
  GLuint current_indices = 0;

  std::vector<Vertex> merged_vertices;
  std::vector<GLuint> merged_indices;

  /**
   * Reserve space for vectors' data on the heap
   */
  mesh_cmds.reserve(meshes.size());

  for (const auto &mesh : meshes) {
    for (const auto &mesh_vert : mesh.vertices) {
      merged_vertices.push_back(mesh_vert);
    }

    for (const auto &mesh_idx : mesh.indices) {
      merged_indices.push_back(mesh_idx + current_vertices);
    }

    current_vertices += mesh.vertices.size();
    current_indices += mesh.indices.size();
  }

  mesh_cmds.push_back(DrawElementsIndirectCommand{
      static_cast<GLuint>(current_indices),
      static_cast<GLuint>(1), // 1 instance
      static_cast<GLuint>(0), // offset from first indice
      static_cast<GLuint>(0), // offset from first vertex
      static_cast<GLuint>(0)  // base instance
  });

  /**
   * Upload data on the GPU (once!)
   */

  r.glGenVertexArrays(1, &vao);
  r.glGenBuffers(1, &vbo);
  r.glGenBuffers(1, &ibo);

  r.glBindVertexArray(vao);

  /**
   * Upload data to ARRAY_BUFFER
   */
  r.glBindBuffer(GL_ARRAY_BUFFER, vbo);
  r.glBufferData(GL_ARRAY_BUFFER, merged_vertices.size() * sizeof(Vertex),
                 merged_vertices.data(),
                 isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);

  /**
   * Upload data to ELEMENT_ARRAY_BUFFER
   */
  r.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  r.glBufferData(
      GL_ELEMENT_ARRAY_BUFFER, merged_indices.size() * sizeof(uint32_t),
      merged_indices.data(), isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);

  texture->load();

  /**
   * Enable in's
   */
  r.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(Vertex, position));

  r.glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(Vertex, texCoords));

  r.glEnableVertexAttribArray(0);
  r.glEnableVertexAttribArray(1);
  r.glBindVertexArray(0);

  /**
   * Cleanup unused meshes
   */
  meshes.clear();
  meshes.shrink_to_fit();
}

void Object::draw() {
  r.glUseProgram(r.shaderProgram);

  r.glBindVertexArray(vao);

  /**
   * Enable uniforms
   */
  r.glActiveTexture(GL_TEXTURE0);
  texture->bind();

  r.glUniformMatrix4fv(r.glGetUniformLocation(r.shaderProgram, "modelMatrix"),
                       1, GL_FALSE, glm::value_ptr(modelMatrix));

  r.glUniformMatrix4fv(r.glGetUniformLocation(r.shaderProgram, "viewMatrix"), 1,
                       GL_FALSE, glm::value_ptr(r.camera->viewMatrix));

  r.glUniformMatrix4fv(
      r.glGetUniformLocation(r.shaderProgram, "projectionMatrix"), 1, GL_FALSE,
      glm::value_ptr(r.camera->projectionMatrix));

  r.glUniform1i(r.glGetUniformLocation(r.shaderProgram, "fTexture"), 0);

  r.glDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, mesh_cmds.data());

  r.glBindVertexArray(0);
}
