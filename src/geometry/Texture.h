#pragma once

#include <QOpenGLExtraFunctions>
#include "Designer.h"

class Texture
{
public:
    GLuint id;
    uint32_t width, height;

    Designer *ds = nullptr;

    Texture(Designer *__ds) : ds(__ds) {};

    void load(QByteArray &blob)
    {
        ds->glGenTextures(1, &id);

        ds->glBindTexture(GL_TEXTURE_2D, id);
        ds->glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        ds->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, blob.data());
        ds->glGenerateMipmap(GL_TEXTURE_2D);
        ds->glTexParameteri(GL_TEXTURE_2D, );

        ds->glBindTexture(GL_TEXTURE_2D, 0);
    }
};