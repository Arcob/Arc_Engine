#pragma once

#include "common/Rendering/Textures/Texture.h"

class Texture2D : public Texture
{
public:
    /*! \brief Constructs a texture object.
    *  \param rawData The raw pointer to the pixel RGBA data.
    *  \param width The width of the texture.
    *  \param height The height of the texture.
    *
    *  Takes in the raw pixel data for a texture and creates an RGBA texture out of it. Note that only RGBA textures are currently
    *  supported. Additionally, we assume the data is stored such it describes the texture from bottom to top, one row at a time (aka
    *  rows are contiguous in memory, beginning from the bottom row).
    */
    Texture2D(GLubyte* rawData, int width, int height);
private:
    int texWidth;
    int texHeight;
};