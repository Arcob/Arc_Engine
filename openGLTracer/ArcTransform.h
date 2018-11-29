#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>    
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>


namespace Arc_Engine {
	class ArcTransform
	{
	public:
		ArcTransform();
		~ArcTransform() = default;
		const glm::vec3 position() const;
		const glm::vec3 scale() const;
		const glm::vec3 rotation() const;
		const glm::quat quaternion() const;
		const glm::mat4 positionMatrix() const;
		const glm::mat4 rotationMatrix() const;
		const glm::mat4 scaleMatrix() const;
		const glm::mat4 transformMatrix() const;
		void setPosition(glm::vec3 position);
		void setScale(glm::vec3 scale);
		void setRotation(glm::vec3 rotation);

	private:
		glm::vec3 _position;
		glm::vec3 _scale;
		glm::vec3 _rotation;
		const glm::mat4 translate(GLfloat x, GLfloat y, GLfloat z) const;
		const glm::mat4 scale(GLfloat x, GLfloat y, GLfloat z) const;
		const glm::mat4 rotate(GLfloat x, GLfloat y, GLfloat z, GLfloat angle) const;
	};
}

