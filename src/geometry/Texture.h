#pragma once

#include "../Designer.h"
#include "QtCore/qnamespace.h"
#include <QtGui/QOpenGLExtraFunctions>
#include <QtOpenGL/QOpenGLTexture>

class Texture {
public:
  GLuint id;
  uint32_t width, height;

  Designer &ds;
  QOpenGLTexture *glTexture = nullptr;

  Texture(Designer &__ds) : ds(__ds) {};

  void load(const QString &path = ":textures/4po4mak.png") {
    glTexture = new QOpenGLTexture(QImage(path).flipped(Qt::Vertical),
                                   QOpenGLTexture::GenerateMipMaps);
    glTexture->setMagnificationFilter(
        QOpenGLTexture::Filter::NearestMipMapNearest);
    glTexture->setMinificationFilter(
        QOpenGLTexture::Filter::NearestMipMapNearest);

    qDebug() << "LOADED TEXTURE" << glTexture->width() << glTexture->height();

    id = glTexture->textureId();

    // ds.glGenTextures(1, &id);

    // ds.glBindTexture(GL_TEXTURE_2D, id);
    // ds.glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // ds.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
    //                 GL_UNSIGNED_BYTE, glTexture-.);
    // ds.glGenerateMipmap(GL_TEXTURE_2D);

    // ds.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // ds.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // ds.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // ds.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    // ds.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // ds.glBindTexture(GL_TEXTURE_2D, 0);
  }

  inline void bind() { ds.glBindTexture(GL_TEXTURE_2D, id); }
  inline void unbind() { ds.glBindTexture(GL_TEXTURE_2D, 0); };
};
