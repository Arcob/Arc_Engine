#pragma once
#include "common.h"

namespace Arc_Engine {

	class ArcRenderer
	{
	public:
		ArcRenderer() = default;
		ArcRenderer(GLuint shaderProgram, size_t vertexDataSize, GLfloat vertexData[], GLuint texture);
		ArcRenderer(std::shared_ptr<class ArcMaterial> material, size_t vertexDataSize, GLfloat vertexData[], GLuint texture);
		~ArcRenderer() = default;

		std::shared_ptr<class ArcMaterial> material;
		GLuint program;
		GLuint texture;
		GLuint vbo;
		GLuint vao;
		GLenum drawType;
		GLint drawStart;
		GLint drawCount;
	};

}

