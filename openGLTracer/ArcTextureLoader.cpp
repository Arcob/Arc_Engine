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
		//2 ����ͼƬ
		FIBITMAP *dib = FreeImage_Load(fifmt, texturePath.c_str(), 0);
		if (!dib) {
			std::cerr << "ERROR: Failed to read in the texture from - " << texturePath.c_str() << std::endl;
			return;
		}

		//3 ת��Ϊrgb 24ɫ
		dib = FreeImage_ConvertTo24Bits(dib);

		//4 ��ȡ����ָ��
		BYTE *pixels = (BYTE*)FreeImage_GetBits(dib);

		int width = FreeImage_GetWidth(dib);
		int height = FreeImage_GetHeight(dib);
		/**
		* ����һ������Id,������Ϊ��������������Ĳ����������������id
		*/
		glGenTextures(1, tempTexture);

		/**
		* ʹ���������id,���߽а�(����)
		*/
		glBindTexture(GL_TEXTURE_2D, *tempTexture);
		/**
		* ָ������ķŴ�,��С�˲���ʹ�����Է�ʽ������ͼƬ�Ŵ��ʱ���ֵ��ʽ
		*/
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		/**
		* ��ͼƬ��rgb�����ϴ���opengl.
		*/
		glTexImage2D(
			GL_TEXTURE_2D, //! ָ���Ƕ�άͼƬ
			0, //! ָ��Ϊ��һ�������������mipmap,��lod,����ľͲ��ü����ģ�Զ��ʹ�ý�С������
			GL_RGB, //! �����ʹ�õĴ洢��ʽ
			width, //! ��ȣ���һ����Կ�����֧�ֲ��������������Ⱥ͸߶Ȳ���2^n��
			height, //! ��ȣ���һ����Կ�����֧�ֲ��������������Ⱥ͸߶Ȳ���2^n��
			0, //! �Ƿ�ı�
			GL_BGR_EXT, //! ���ݵĸ�ʽ��bmp�У�windows,����ϵͳ�д洢��������bgr��ʽ
			GL_UNSIGNED_BYTE, //! ������8bit����
			pixels
		);

		//std::cout << dib << std::endl;
		/**
		* �ͷ��ڴ�
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
