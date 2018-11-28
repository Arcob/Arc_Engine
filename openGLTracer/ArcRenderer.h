#pragma once
#include <GL/glew.h>   

namespace Arc_Engine {

	class ArcRenderer
	{
	public:
		ArcRenderer() = default;
		~ArcRenderer() = default;

		GLuint program;
		GLuint texture;
		GLuint vbo;
		GLuint vao;
		GLenum drawType;
		GLint drawStart;
		GLint drawCount;
	};

}

