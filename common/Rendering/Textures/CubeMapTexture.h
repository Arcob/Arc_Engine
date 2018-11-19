#pragma once

#include "common/Rendering/Textures/Texture.h"

class CubeMapTexture : public Texture
{
public:
    // right, left, top, bottom, back, forward
    CubeMapTexture(GLubyte* data[6], int width, int height);

private:
    int texWidth;
    int texHeight;
};