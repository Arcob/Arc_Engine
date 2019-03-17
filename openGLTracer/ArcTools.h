#pragma once
#include "common.h"
#include "DriverSetting.h"

namespace Arc_Engine {

	class ArcTools
	{
	public:
		static std::string getCurrentPath();
		static void drawDebugQuad(GLuint texture);
		static void drawPostEffectQuad(GLuint texture, GLuint gbuffer, GLuint positionMap, const glm::mat4 proj);
		static GLuint generateSSAONoiceTextures();
		static GLfloat lerp(GLfloat a, GLfloat b, GLfloat f);
		static void RenderQuad();

	private:
		static std::string debug_depth_vert_shader_path;
		static std::string debug_depth_frag_shader_path;
		static std::vector<glm::vec3> ssaoNoise;
		static std::string _currentPath;
		static GLuint quadVAO;
		static GLuint quadVBO;
		static GLuint debugDepthShaderProgram;
		static GLuint PostEffectProgram;
		static GLuint noiseTexture;
		static GLuint g_buffer;
		
		static GLfloat sampleArray[64 * 3];
	};
}

