#include "stdafx.h"
#include "Swb_TextureLoader.h"
#include "FreeImage.h"


namespace Swb_TextureLoader 
{
	GLuint loadImage() {
		GLuint _textureId;

		FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType("woodfloor.tga", 0);

		//2 加载图片
		FIBITMAP *dib = FreeImage_Load(fifmt, "woodfloor.tga", 0);

		//3 转化为rgb 24色
		dib = FreeImage_ConvertTo24Bits(dib);

		//4 获取数据指针
		BYTE *pixels = (BYTE*)FreeImage_GetBits(dib);

		int width = FreeImage_GetWidth(dib);
		int height = FreeImage_GetHeight(dib);

		/**
		* 产生一个纹理Id,可以认为是纹理句柄，后面的操作将书用这个纹理id
		*/
		glGenTextures(1, &_textureId);

		/*
		* 使用这个纹理id,或者叫绑定(关联)
		*/
		glBindTexture(GL_TEXTURE_2D, _textureId);
		/**
		* 指定纹理的放大,缩小滤波，使用线性方式，即当图片放大的时候插值方式
		*/
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		/**
		* 将图片的rgb数据上传给opengl.
		*/
		glTexImage2D(
			GL_TEXTURE_2D, //! 指定是二维图片
			0, //! 指定为第一级别，纹理可以做mipmap,即lod,离近的就采用级别大的，远则使用较小的纹理
			GL_RGB, //! 纹理的使用的存储格式
			width, //! 宽度，老一点的显卡，不支持不规则的纹理，即宽度和高度不是2^n。
			height, //! 宽度，老一点的显卡，不支持不规则的纹理，即宽度和高度不是2^n。
			0, //! 是否的边
			GL_BGR_EXT, //! 数据的格式，bmp中，windows,操作系统中存储的数据是bgr格式
			GL_UNSIGNED_BYTE, //! 数据是8bit数据
			pixels
		);
		/**
		* 释放内存
		*/
		FreeImage_Unload(dib);

		return _textureId;
	}

	static unsigned char* DecodeBMPData(unsigned char* imageData, int&width, int& heigh)
	{
		//decode bmp
		int pixelDataOffset = *((int*)(imageData + 10));
		width = *((int*)(imageData + 18));
		heigh = *((int*)(imageData + 22));
		unsigned char* pixelData = (imageData + pixelDataOffset);
		for (int i = 0; i < width*heigh * 3; i += 3)
		{
			//bgr->rgb
			unsigned char temp = pixelData[i + 2];
			pixelData[i + 2] = pixelData[i];
			pixelData[i] = temp;
		}
		return pixelData;
	}

	static unsigned char* DecodeDXT1Data(unsigned char* imageData, int&width, int& height, int& pixelSize)
	{
		height = *(unsigned long*)(imageData + sizeof(unsigned long) * 3);
		width = *(unsigned long*)(imageData + sizeof(unsigned long) * 4);
		pixelSize = *(unsigned long*)(imageData + sizeof(unsigned long) * 5);
		unsigned long compressFormate;
		compressFormate = *(unsigned long*)(imageData + sizeof(unsigned long) * 21);

		switch (compressFormate)
		{
		case FORMATE_DXT1:
			printf("DXT1\n");
			break;
		default:
			break;
		}
		unsigned char* pixelData = new unsigned char[pixelSize];
		memcpy(pixelData, (imageData + sizeof(unsigned long) * 32), pixelSize);

		return pixelData;
	}

	static char* LoadFileContent(const char* imagePath) {
		std::ifstream v(imagePath);
		std::string vertBuffer((std::istreambuf_iterator<char>(v)), std::istreambuf_iterator<char>());
		//int length = vertBuffer.length + 1;
		char* result = new char[11];
		//strcpy(result, vertBuffer.c_str());
		return result;
	}

	GLuint CreateTextureFromFile(const char* imagePath)
	{
		unsigned char* imageData = (unsigned char*)LoadFileContent(imagePath);

		int width = 0;
		int heigh = 0;
		//decode bmp
		unsigned char* pixelData = nullptr;
		int pixelDataSize = 0;
		GLenum srcForamte = GL_RGB;
		if ((*(unsigned short*)imageData) == 0x4D42)
		{
			pixelData = DecodeBMPData(imageData, width, heigh);
		}
		else if (memcmp(imageData, "DDS ", 4) == 0)
		{
			pixelData = DecodeDXT1Data(imageData, width, heigh, pixelDataSize);
			srcForamte = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		}

		if (pixelData == nullptr)
		{
			printf("cannot decode %s \n", imagePath);
			delete imageData;
			return 0;
		}

		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		if (srcForamte == GL_RGB) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, heigh, 0, GL_RGB, GL_UNSIGNED_BYTE, pixelData);
		}
		else if (srcForamte == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT)
		{
			glCompressedTexImage2D(GL_TEXTURE_2D, 0, srcForamte, width, heigh, 0, pixelDataSize, pixelData);
		}
		glBindBuffer(GL_TEXTURE_2D, 0);
		delete imageData;
		return texture;
	}

}
