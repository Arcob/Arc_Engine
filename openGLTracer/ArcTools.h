#pragma once
#include "common.h"
#include "DriverSetting.h"

namespace Arc_Engine {

	class ArcTools
	{
	public:
		static std::string getCurrentPath();
		static void drawDebugQuad(GLuint texture);
		static void RenderQuad();

	private:
		static std::string debug_depth_vert_shader_path;
		static std::string debug_depth_frag_shader_path;

		static std::string _currentPath;
		static GLuint quadVAO;
		static GLuint quadVBO;
		static GLuint debugDepthShaderProgram;

	};
}

