#pragma once

#include "Renderer.h"
#include <QtGui/QOpenGLExtraFunctions>
#include <QtOpenGL/QOpenGLTexture>

class Texture {
public:
  GLuint id;
  uint32_t width, height;

  Renderer &r;
  QOpenGLTexture *glTexture = nullptr;

  explicit Texture(Renderer &__r);

  void load(const QString &path = ":textures/4po4mak.png");

  inline void bind() {
    if (glTexture)
      glTexture->bind();
  }
};
