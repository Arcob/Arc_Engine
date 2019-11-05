#include "ArcPostEffectManager.h"
#include "ArcTextureLoader.h"
#include "ArcTools.h"
#include <random>

namespace Arc_Engine {
	GLuint ArcPostEffectManager::_postEffectProgram = -1;
	GLuint ArcPostEffectManager::_postEffectFBO = 0;

	GLuint ArcPostEffectManager::_ssaoProgram = -1;
	GLuint ArcPostEffectManager::_ssaoTexture = 0;
	GLuint ArcPostEffectManager::_noiseTexture = 0;
	std::vector<glm::vec3> ArcPostEffectManager::_ssaoNoise;
	GLfloat ArcPostEffectManager::_sampleArray[64 * 3];

	std::string ArcPostEffectManager::quad_vert_shader_path = "\\QuadShader\\screen_quad_vert.vert";
	std::string ArcPostEffectManager::quad_frag_shader_path = "\\QuadShader\\screen_quad_frag.frag";

	std::string ArcPostEffectManager::ssao_vert_shader_path = "\\QuadShader\\ssao_vert.vert";
	std::string ArcPostEffectManager::ssao_frag_shader_path = "\\QuadShader\\ssao_frag.frag";

	GLuint ArcPostEffectManager::postEffectFBO() {
		return _postEffectFBO;
	}

	GLuint ArcPostEffectManager::generatePostEffectProgram() {
		if (_postEffectProgram == -1) {
			_postEffectProgram = Arc_Engine::ArcMaterial::loadShaderAndCreateProgram(ArcTools::getCurrentPath() + shader_path + quad_vert_shader_path, ArcTools::getCurrentPath() + shader_path + quad_frag_shader_path);
		}
		return _postEffectProgram;
	}

	GLuint ArcPostEffectManager::generateSSAOProgram() {
		if (_ssaoProgram == -1) {
			_ssaoProgram = Arc_Engine::ArcMaterial::loadShaderAndCreateProgram(ArcTools::getCurrentPath() + shader_path + ssao_vert_shader_path, ArcTools::getCurrentPath() + shader_path + ssao_frag_shader_path);
		}
		return _ssaoProgram;
	}

	GLuint ArcPostEffectManager::generatePostEffectFBO() {
		if (_postEffectFBO <= 0 && _ssaoTexture <= 0) {
			glGenFramebuffers(1, &_postEffectFBO);
			glBindFramebuffer(GL_FRAMEBUFFER, _postEffectFBO);
			Arc_Engine::ArcTextureLoader::createDefaultRGBA16FMap(&_ssaoTexture);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _ssaoTexture, 0);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		return _postEffectFBO;
	}

	void ArcPostEffectManager::drawPostEffectQuad(GLuint texture, GLuint gbuffer, GLuint positionMap, const glm::mat4 proj) {
		glViewport(0, 0, WIDTH * ANTI_AILASING_MULTY_TIME, HEIGHT * ANTI_AILASING_MULTY_TIME);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(_postEffectProgram);
		glUniform1f(glGetUniformLocation(_postEffectProgram, "near_plane"), 1.0f);
		glUniform1f(glGetUniformLocation(_postEffectProgram, "far_plane"), 7.5f);

		GLint texLocation = glGetUniformLocation(_postEffectProgram, "screenTexture");
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(texLocation, 0);

		GLint texLocation1 = glGetUniformLocation(_postEffectProgram, "SSAOMap");
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _ssaoTexture);
		glUniform1i(texLocation1, 1);

		ArcTools::RenderQuad();
		glUseProgram(0);
	}

	GLuint ArcPostEffectManager::generateSSAONoiceTextures() {
		std::uniform_real_distribution<GLfloat> randomFloats(0.0, 1.0); // Ëæ»ú¸¡µãÊý£¬·¶Î§0.0 - 1.0
		std::default_random_engine generator;
		std::vector<glm::vec3> ssaoKernel;
		for (GLuint i = 0; i < 64; ++i)
		{
			glm::vec3 sample(
				randomFloats(generator) * 2.0 - 1.0,
				randomFloats(generator) * 2.0 - 1.0,
				randomFloats(generator)
			);
			sample = glm::normalize(sample);
			sample *= randomFloats(generator);
			GLfloat scale = GLfloat(i) / 64.0;
			scale = ArcTools::lerp(0.1f, 1.0f, scale * scale);
			sample *= scale;
			ssaoKernel.push_back(sample);
		}

		for (GLuint i = 0; i < 16; i++)
		{
			glm::vec3 noise(
				randomFloats(generator) * 2.0 - 1.0,
				randomFloats(generator) * 2.0 - 1.0,
				0.0f);
			_ssaoNoise.push_back(noise);
		}

		for (int i = 0; i < 64 * 3; i++) {
			if (i % 3 == 0) {
				_sampleArray[i] = ssaoKernel[i / 3].x;
			}
			else if (i % 3 == 1) {
				_sampleArray[i] = ssaoKernel[i / 3].y;
			}
			else if (i % 3 == 2) {
				_sampleArray[i] = ssaoKernel[i / 3].z;
			}
		}

		glGenTextures(1, &_noiseTexture);
		glBindTexture(GL_TEXTURE_2D, _noiseTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 4, 4, 0, GL_RGB, GL_FLOAT, &_ssaoNoise[0]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		return _noiseTexture;
	}

	void ArcPostEffectManager::generateSSAOTexture(GLuint gbuffer, GLuint positionMap, const glm::mat4 proj) {
		glViewport(0, 0, WIDTH * ANTI_AILASING_MULTY_TIME, HEIGHT * ANTI_AILASING_MULTY_TIME);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(_ssaoProgram);
		glUniform1f(glGetUniformLocation(_ssaoProgram, "near_plane"), 1.0f);
		glUniform1f(glGetUniformLocation(_ssaoProgram, "far_plane"), 7.5f);

		GLint texLocation1 = glGetUniformLocation(_ssaoProgram, "gbufferTexture");
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, gbuffer);
		glUniform1i(texLocation1, 1);

		GLint texLocation2 = glGetUniformLocation(_ssaoProgram, "texNoise");
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, _noiseTexture);
		glUniform1i(texLocation2, 2);

		GLint texLocation3 = glGetUniformLocation(_ssaoProgram, "positionTexture");
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, positionMap);
		glUniform1i(texLocation3, 3);

		GLint array = glGetUniformLocation(_ssaoProgram, "samples");
		glUniform3fv(array, 64 * 3, _sampleArray);

		GLint modelMatLocation = glGetUniformLocation(_ssaoProgram, "projection");
		glUniformMatrix4fv(modelMatLocation, 1, GL_FALSE, glm::value_ptr(proj));

		ArcTools::RenderQuad();
		glUseProgram(0);
	}
}
