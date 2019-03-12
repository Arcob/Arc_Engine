#include "ArcRenderer.h"
#include "ArcMaterial.h"

namespace Arc_Engine {
	ArcRenderer::ArcRenderer(GLuint shaderProgram, size_t vertexDataSize, GLfloat vertexData[], GLuint texture) :
		program(shaderProgram), drawType(GL_TRIANGLES), drawStart(0), drawCount(6*2*3), texture(texture)
	{
		//vbo做的事
		glGenBuffers(1, &vbo);//创建缓存对象并且返回缓存对象的标示符
		glBindBuffer(GL_ARRAY_BUFFER, vbo);//当缓存对象创建之后，在使用缓存对象之前，我们需要将缓存对象连接到相应的缓存上。
		glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexData, GL_STATIC_DRAW);
		
		//vao做的事
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		
		glEnableVertexAttribArray(0);//vert
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), NULL);

		glEnableVertexAttribArray(1);//uv
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));

		glEnableVertexAttribArray(2);//normal
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (const GLvoid*)(5 * sizeof(GLfloat)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	ArcRenderer::ArcRenderer(std::shared_ptr<ArcMaterial> material, size_t vertexDataSize, GLfloat vertexData[], GLuint texture) :
		_material(material), program(material->program()), drawType(GL_TRIANGLES), drawStart(0), drawCount(6 * 2 * 3), texture(texture)
	{
		//vbo做的事
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexData, GL_STATIC_DRAW);

		//vao做的事
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		
		glEnableVertexAttribArray(0);//vert
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), NULL);

		glEnableVertexAttribArray(1);//uv
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));

		glEnableVertexAttribArray(2);//normal
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (const GLvoid*)(5 * sizeof(GLfloat)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	
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
