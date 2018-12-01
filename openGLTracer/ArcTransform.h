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
		void translate(glm::vec3 offset);
		void rotate(glm::vec3 eularAngle);
		void rotate(float rightAngle, float upAngle, float forwardAngle);
		void lookAt(glm::vec3 target);

		glm::vec3 forward() const; //Vector3(0, 0, 1)
		glm::vec3 right() const; //Vector3(1, 0, 0)
		glm::vec3 up() const; //Vector3(0, 1, 0)
	private:
		glm::vec3 _position;
		glm::vec3 _scale;
		glm::vec3 _rotation;

		void normalizeRotation();
	};
}

