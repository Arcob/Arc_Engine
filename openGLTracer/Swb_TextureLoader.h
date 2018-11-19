#pragma once
#ifndef __SWB_TEXTURE_LOADER__
#define __SWB_TEXTURE_LOADER__

#include <fstream>
#include <iostream>
#include <streambuf>
#include <vector>
// GLEW    
#define GLEW_STATIC    
#include <GL/glew.h>    

// GLFW    
#include <GLFW/glfw3.h>   

/*class Swb_TextureLoader
{
public:
	Swb_TextureLoader();
	~Swb_TextureLoader();
};*/

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

