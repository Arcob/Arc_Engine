#include "ArcTools.h"

namespace Arc_Engine {
	std::string ArcTools::_currentPath = "";
	GLuint ArcTools::quadVAO = 0;
	GLuint ArcTools::quadVBO = 0;
	GLuint ArcTools::debugDepthShaderProgram = -1;
	std::string ArcTools::debug_depth_vert_shader_path = "\\shadowShader\\shadow_vert.vert";
	std::string ArcTools::debug_depth_frag_shader_path = "\\shadowShader\\shadow_frag.frag";

	const std::string quad_vert_shader_path = "\\QuadShader\\quad_vert.vert";
	const std::string quad_frag_shader_path = "\\QuadShader\\quad_frag.frag";

	std::string ArcTools::getCurrentPath() {
		if (_currentPath.compare("") == 0) {
			char buf[80];
			_getcwd(buf, sizeof(buf)); //将当前工作目录的绝对路径复制到参数buffer所指的内存空间中
			std::string path1 = std::string(buf);
			std::size_t found = path1.find_last_of("/\\");
			_currentPath = path1.substr(0, found);
		}
		return _currentPath;
	}

	void ArcTools::drawDebugQuad(GLuint texture) {
		if (debugDepthShaderProgram == -1) {
			debugDepthShaderProgram = Arc_Engine::ArcMaterial::loadShaderAndCreateProgram(getCurrentPath() + shader_path + debug_depth_vert_shader_path, getCurrentPath() + shader_path + debug_depth_frag_shader_path);
		}
		glViewport(0, 0, WIDTH, HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(debugDepthShaderProgram);
		glUniform1f(glGetUniformLocation(debugDepthShaderProgram, "near_plane"), 1.0f);
		glUniform1f(glGetUniformLocation(debugDepthShaderProgram, "far_plane"), 7.5f);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		RenderQuad();
		glUseProgram(0);
	}

	void ArcTools::drawPostEffectQuad(GLuint texture) {
		if (debugDepthShaderProgram == -1) {
			debugDepthShaderProgram = Arc_Engine::ArcMaterial::loadShaderAndCreateProgram(getCurrentPath() + shader_path + quad_vert_shader_path, getCurrentPath() + shader_path + quad_frag_shader_path);
		}
		glViewport(0, 0, WIDTH, HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(debugDepthShaderProgram);
		glUniform1f(glGetUniformLocation(debugDepthShaderProgram, "near_plane"), 1.0f);
		glUniform1f(glGetUniformLocation(debugDepthShaderProgram, "far_plane"), 7.5f);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		RenderQuad();
		glUseProgram(0);
	}

	void ArcTools::RenderQuad()
	{
		if (quadVAO == 0)
		{
			GLfloat quadVertices[] = {
				// Positions        // Texture Coords
				-1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
				-1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
				 1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
				 1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
			};
			// Setup plane VAO
			glGenVertexArrays(1, &quadVAO);
			glGenBuffers(1, &quadVBO);
			glBindVertexArray(quadVAO);
			glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		}
		glBindVertexArray(quadVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
	}
}