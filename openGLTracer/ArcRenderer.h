#pragma once
#include "common.h"

namespace Arc_Engine {

	struct layoutStruct {
	public:
		layoutStruct(int index, GLint size, GLint totalLength, GLint phase, int dataSize);
		int _index;
		GLint _width;
		GLint _totalLength;
		GLint _phase;
		int _dataSize;
	};
	
	class ArcRenderer
	{
	public:
		ArcRenderer() = default;
		ArcRenderer(std::shared_ptr<class ArcMaterial> material, size_t vertexDataSize, GLfloat vertexData[], GLuint texture, const std::vector<layoutStruct>& layoutVector);

		~ArcRenderer() = default;

		std::shared_ptr<class ArcMaterial> _material;
		GLuint program;
		GLuint texture;
		GLuint vbo;
		GLuint vao;
		GLenum drawType;
		GLint drawStart;
		GLint drawCount;
	};

	

}

