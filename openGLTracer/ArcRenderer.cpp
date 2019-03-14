#include "ArcRenderer.h"
#include "ArcMaterial.h"

namespace Arc_Engine {

	ArcRenderer::ArcRenderer(std::shared_ptr<ArcMaterial> material, size_t vertexDataSize, GLfloat vertexData[], GLuint texture, const std::vector<layoutStruct>& layoutVector) :
		_material(material), program(material->program()), drawType(GL_TRIANGLES), drawStart(0), drawCount(6 * 2 * 3), texture(texture)
	{
		//vbo做的事
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexData, GL_STATIC_DRAW);

		//vao做的事
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		for (int i = 0; i < layoutVector.size(); i++) {
			glEnableVertexAttribArray(layoutVector[i]._index);
			glVertexAttribPointer(layoutVector[i]._index, layoutVector[i]._width, GL_FLOAT, GL_FALSE, layoutVector[i]._totalLength * layoutVector[i]._dataSize, (const GLvoid*)(layoutVector[i]._phase * layoutVector[i]._dataSize));
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	layoutStruct::layoutStruct(int index, GLint size, GLint totalLength, GLint phase, int dataSize): _index(index), _width(size), _totalLength(totalLength), _phase(phase), _dataSize(dataSize){}
	
	/*std::shared_ptr<ArcRenderer> ArcRenderer::createRenderer(GLuint shaderProgram, GLfloat vertexData[], GLuint* texture) {
		auto renderer = std::make_shared<ArcRenderer>();
		renderer->program = shaderProgram;
		renderer->drawType = GL_TRIANGLES;
		renderer->drawStart = 0;
		renderer->drawCount = 6 * 2 * 3;
		renderer->texture = *texture;

		glGenBuffers(1, &renderer->vbo);
		glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);

		glGenVertexArrays(1, &renderer->vao);
		glBindVertexArray(renderer->vao);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);//vert
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), NULL);

		glEnableVertexAttribArray(1);//uv
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));

		glEnableVertexAttribArray(2);//normal
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (const GLvoid*)(5 * sizeof(GLfloat)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		return std::move(renderer);
	}*/
}

/*ArcRenderer::ArcRenderer()
{
}


ArcRenderer::~ArcRenderer()
{
}*/
