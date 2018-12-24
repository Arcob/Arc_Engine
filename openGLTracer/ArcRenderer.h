#pragma once
#include "common.h"

namespace Arc_Engine {

	class ArcRenderer
	{
	public:
		ArcRenderer() = default;
		ArcRenderer(GLuint shaderProgram, size_t vertexDataSize, GLfloat vertexData[], GLuint texture);
		~ArcRenderer() = default;

		GLuint program;
		GLuint texture;
		GLuint vbo;
		GLuint vao;
		GLenum drawType;
		GLint drawStart;
		GLint drawCount;

		static std::shared_ptr<ArcRenderer> createRenderer(GLuint shaderProgram, GLfloat vertexData[], GLuint* texture);
	};

}

