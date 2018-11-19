#include "common/Rendering/Textures/Texture.h"

Texture::Texture(GLenum inputTarget) :
    textureTarget(inputTarget)
{
}

Texture::~Texture()
{
    OGL_CALL(glDeleteTextures(1, &glTexture));
}

void Texture::BeginRender(int unit) const
{
    OGL_CALL(glActiveTexture(GL_TEXTURE0 + unit));
    OGL_CALL(glBindTexture(textureTarget, glTexture));
}

void Texture::EndRender() const
{
    OGL_CALL(glBindTexture(textureTarget, 0));
}

