#include "common/Rendering/Textures/CubeMapTexture.h"

CubeMapTexture::CubeMapTexture(GLubyte* data[6], int width, int height):
    Texture(GL_TEXTURE_CUBE_MAP), texWidth(width), texHeight(height)
{
    OGL_CALL(glGenTextures(1, &glTexture));
    OGL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, glTexture));
    OGL_CALL(glTexStorage2D(GL_TEXTURE_CUBE_MAP, 4, GL_RGBA8, texWidth, texHeight));
    for (int i = 0; i < 6; ++i) {
        OGL_CALL(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, 0, 0, texWidth, texHeight, GL_RGBA, GL_UNSIGNED_BYTE, data[i]));
    }
    
    // Would be useful to expose these settings!
    OGL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    OGL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    OGL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    OGL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    OGL_CALL(glGenerateMipmap(GL_TEXTURE_CUBE_MAP));

    OGL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}