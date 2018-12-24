#pragma once
#include "common.h"
namespace Arc_Engine {

	class ArcTextureLoader
	{
	public:
		static void loadImageToTexture(std::string texturePath, GLuint* tempTexture);
	};
	
}

