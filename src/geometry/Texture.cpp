#include "Texture.h"

Texture::Texture(Renderer &__r) : r(__r) {};

void Texture::load(const QString &path) {
  glTexture = new QOpenGLTexture(QImage(path).flipped(Qt::Vertical),
                                 QOpenGLTexture::GenerateMipMaps);
  glTexture->setMagnificationFilter(
      QOpenGLTexture::Filter::NearestMipMapNearest);
  glTexture->setMinificationFilter(
      QOpenGLTexture::Filter::NearestMipMapNearest);

  qDebug() << "LOADED TEXTURE" << glTexture->width() << glTexture->height();

  id = glTexture->textureId();
}
