#include "common/Rendering/Textures/Texture2D.h"

Texture2D::Texture2D(GLubyte* rawData, int width, int height):
    Texture(GL_TEXTURE_2D), texWidth(width), texHeight(height)
{
    OGL_CALL(glGenTextures(1, &glTexture));
    OGL_CALL(glBindTexture(GL_TEXTURE_2D, glTexture));
    OGL_CALL(glTexStorage2D(GL_TEXTURE_2D, 4, GL_RGBA8, texWidth, texHeight));
    OGL_CALL(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, texWidth, texHeight, GL_RGBA, GL_UNSIGNED_BYTE, rawData));

    // Would be useful to expose these settings!
    OGL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    OGL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    OGL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    OGL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    OGL_CALL(glGenerateMipmap(GL_TEXTURE_2D));

    OGL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}