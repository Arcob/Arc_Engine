#pragma once
#include "common.h"
#include "DriverSetting.h"

namespace Arc_Engine {
	class ArcPostEffectManager
	{
	public:
		static void drawPostEffectQuad(GLuint texture, GLuint gbuffer, GLuint positionMap, const glm::mat4 proj);
		static GLuint generatePostEffectFBO();
		static GLuint generatePostEffectProgram();
		static GLuint generateSSAOProgram();
		static GLuint postEffectFBO();

		static void generateSSAOTexture(GLuint gbuffer, GLuint positionMap, const glm::mat4 proj);
		static GLuint generateSSAONoiceTextures();

	private:
		static GLuint _postEffectProgram;
		static GLuint _postEffectFBO;
		static std::string quad_vert_shader_path;
		static std::string quad_frag_shader_path;

		static std::string ssao_vert_shader_path;
		static std::string ssao_frag_shader_path;
		static std::vector<glm::vec3> _ssaoNoise;		
		static GLuint _noiseTexture;
		static GLuint _ssaoProgram;
		static GLuint _ssaoTexture;
		static GLfloat _sampleArray[64 * 3];
	};
}

