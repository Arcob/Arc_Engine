#pragma once
#ifndef __SWB_TEXTURE_LOADER__
#define __SWB_TEXTURE_LOADER__

#include "common.h"

namespace Swb_TextureLoader 
{
	//GLuint _textureId;

	const unsigned long  FORMATE_DXT1 = 0x31545844l; //DXT1-> 1 T X D

	static unsigned char* DecodeBMPData(unsigned char* imageData, int&width, int& heigh);
	static unsigned char* DecodeDXT1Data(unsigned char* imageData, int&width, int& height, int& pixelSize);
	static char* LoadFileContent(const char* imagePath);
	GLuint CreateTextureFromFile(const char* imagePath);
}

#endif

