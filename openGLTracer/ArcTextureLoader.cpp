#include "ArcTextureLoader.h"
#include "FreeImage.h"
#include "DriverSetting.h"

namespace Arc_Engine {
	void ArcTextureLoader::loadImageToTexture(const std::string& texturePath, GLuint* tempTexture) {
		FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(texturePath.c_str(), 0);
		if (fifmt == FIF_UNKNOWN) {
			fifmt = FreeImage_GetFIFFromFilename(texturePath.c_str());
		}
		if (fifmt == FIF_UNKNOWN) {
			std::cerr << "ERROR: Failed to determine the filetype for " << texturePath.c_str() << std::endl;
			return;
		}
		//std::cout << texturePath.c_str() << std::endl;
		//2 加载图片
		FIBITMAP *dib = FreeImage_Load(fifmt, texturePath.c_str(), 0);
		if (!dib) {
			std::cerr << "ERROR: Failed to read in the texture from - " << texturePath.c_str() << std::endl;
			return;
		}

		//3 转化为rgb 24色
		dib = FreeImage_ConvertTo24Bits(dib);

		//4 获取数据指针
		BYTE *pixels = (BYTE*)FreeImage_GetBits(dib);

		int width = FreeImage_GetWidth(dib);
		int height = FreeImage_GetHeight(dib);
		/**
		* 产生一个纹理Id,可以认为是纹理句柄，后面的操作将书用这个纹理id
		*/
		glGenTextures(1, tempTexture);

		/**
		* 使用这个纹理id,或者叫绑定(关联)
		*/
		glBindTexture(GL_TEXTURE_2D, *tempTexture);
		/**
		* 指定纹理的放大,缩小滤波，使用线性方式，即当图片放大的时候插值方式
		*/
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
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

		//std::cout << dib << std::endl;
		/**
		* 释放内存
		*/
		FreeImage_Unload(dib);
	}

	void ArcTextureLoader::createDepthMap(GLuint shadowWidth, GLuint shadowHeight, GLuint* depthMap) {
		glGenTextures(1, depthMap);
		glBindTexture(GL_TEXTURE_2D, *depthMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
			shadowWidth, shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	}

	void ArcTextureLoader::createDepthMap(GLuint* depthMap) {
		createDepthMap(WIDTH, HEIGHT, depthMap);
	}
	
	void ArcTextureLoader::createPostEffectMap(GLuint postEffectWidth, GLuint postEffectHeight, GLuint* postEffectMap) {
		glGenTextures(1, postEffectMap);
		glBindTexture(GL_TEXTURE_2D, *postEffectMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, postEffectWidth, postEffectHeight, 0, GL_RGBA, GL_FLOAT, NULL);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, postEffectWidth, postEffectHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

	}

	void ArcTextureLoader::createPostEffectMap(GLuint* postEffectMap) {
		createPostEffectMap(WIDTH * ANTI_AILASING_MULTY_TIME, HEIGHT * ANTI_AILASING_MULTY_TIME, postEffectMap);
	}
	
	void ArcTextureLoader::createGBufferMap(GLuint width, GLuint height, GLuint* tempTexture) {
		glGenTextures(1, tempTexture);
		glBindTexture(GL_TEXTURE_2D, *tempTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void ArcTextureLoader::createGBufferMap(GLuint* tempTexture) {
		createGBufferMap(WIDTH * ANTI_AILASING_MULTY_TIME, HEIGHT * ANTI_AILASING_MULTY_TIME, tempTexture);
	}
}
