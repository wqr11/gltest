#pragma once

#include "Mesh.h"
#include <QtGui/QOpenGLExtraFunctions>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>

class Texture;
class Renderer;

struct DrawElementsIndirectCommand {
  GLuint count;         // Количество индексов для этого дровы (element count)
  GLuint instanceCount; // Количество инстансов (instance count)
  GLuint firstIndex;    // Смещение в элементах (first index)
  GLuint baseVertex;    // Смещение вершин (base vertex)
  GLuint baseInstance;  // Базовый инстанс (base instance)
};

class Object {
protected:
  GLuint vao; // Vertex Array Object (settings)
  GLuint vbo; // Vertex Buffer Object
  GLuint ibo; // Index Buffer Object
  Renderer &r;
  std::vector<DrawElementsIndirectCommand> mesh_cmds;
  std::vector<Mesh> meshes;
  std::shared_ptr<Texture> texture;

public:
  explicit inline Object(Renderer &__ds, std::shared_ptr<Texture> __texture)
      : r(__ds), texture(__texture) {};

  glm::mat4 modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));

  void upload(bool isStatic = false);
  void draw();
};
