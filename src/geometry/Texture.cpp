#include "Texture.h"
#include <QtOpenGL/QOpenGLTexture>

Texture::Texture(Renderer &__r) : r(__r) {};

void Texture::load(const QString &path) {
  map = new QOpenGLTexture(QImage(path).flipped(),
                           QOpenGLTexture::GenerateMipMaps);

  map->setMagnificationFilter(QOpenGLTexture::Filter::NearestMipMapNearest);
  map->setMinificationFilter(QOpenGLTexture::Filter::NearestMipMapNearest);

  qDebug() << "LOADED TEXTURE" << map->width() << map->height();

  id = map->textureId();
}
