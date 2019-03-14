#pragma once
#include "common.h"
namespace Arc_Engine {

	class ArcTextureLoader
	{
	public:
		static void loadImageToTexture(const std::string& texturePath, GLuint* tempTexture);

		static void createDepthMap(GLuint* tempTexture); //默认的width和height都是1024

		static void createDepthMap(GLuint shadowWidth, GLuint shadowHeight, GLuint* tempTexture);

		static void createPostEffectMap(GLuint* tempTexture); //默认的width和height都是1024

		static void createPostEffectMap(GLuint shadowWidth, GLuint shadowHeight, GLuint* tempTexture);
	};
	
}

