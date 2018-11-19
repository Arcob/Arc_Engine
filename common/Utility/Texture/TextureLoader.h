#pragma once

#ifndef __TEXTURE_LOADER__
#define __TEXTURE_LOADER__

#include "common/common.h"

class Texture2D;
class CubeMapTexture;

namespace TextureLoader
{
GLubyte* LoadRawData(const std::string& filename, int& width, int& height);
std::shared_ptr<Texture2D> LoadTexture(const std::string& filename);
std::shared_ptr<CubeMapTexture> LoadCubeTexture(const std::string& front, const std::string& left, const std::string& right,
    const std::string& top, const std::string& bottom, const std::string& back);

}
#endif
