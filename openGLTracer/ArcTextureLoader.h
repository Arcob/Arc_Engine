#pragma once
#include "common.h"
namespace Arc_Engine {

	class ArcTextureLoader
	{
	public:
		static void loadImageToTexture(const std::string& texturePath, GLuint* tempTexture);

		static void createDepthMap(GLuint* tempTexture); //Ĭ�ϵ�width��height����1024

		static void createDepthMap(GLuint shadowWidth, GLuint shadowHeight, GLuint* tempTexture);

		static void createDefaultRGBA16FMap(GLuint shadowWidth, GLuint shadowHeight, GLuint* tempTexture);

		static void createDefaultRGBA16FMap(GLuint* tempTexture);
	};
	
}

