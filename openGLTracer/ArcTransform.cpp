#include "ArcTransform.h"

namespace Arc_Engine {

	ArcTransform::ArcTransform():
		_position(0.0f,0.0f,0.0f),
		_scale(1.0f,1.0f,1.0f),
		_rotation(0.0f,0.0f,0.0f)
	{
	}


	/*ArcTransform::~ArcTransform()
	{
	}*/

	const glm::vec3 ArcTransform::position() const {
		return _position;
	}

	const glm::vec3 ArcTransform::scale() const {
		return _scale;
	}

	const glm::vec3 ArcTransform::rotation() const {
		return _rotation;
	}

	const glm::quat ArcTransform::quaternion() const {
		return glm::quat(_rotation);
	}

	const glm::mat4 ArcTransform::positionMatrix() const {
		return glm::translate(glm::mat4(), _position);
	}

	const glm::mat4 ArcTransform::rotationMatrix() const {
		glm::mat4 orientation;
		orientation = glm::rotate(orientation, glm::radians(_rotation.x), glm::vec3(1, 0, 0));
		orientation = glm::rotate(orientation, glm::radians(_rotation.y), glm::vec3(0, 1, 0));
		orientation = glm::rotate(orientation, glm::radians(_rotation.z), glm::vec3(0, 0, 1));
		return orientation;
	}

	const glm::mat4 ArcTransform::scaleMatrix() const {
		return glm::scale(glm::mat4(), _scale);
	}

	const glm::mat4 ArcTransform::transformMatrix() const {
		return positionMatrix() * rotationMatrix() * scaleMatrix();// *glm::rotate(glm::mat4(), glm::length(_rotation), glm::normalize(_rotation));
	}

	void ArcTransform::setPosition(glm::vec3 position) {
		_position = position;
	}

	void ArcTransform::setScale(glm::vec3 scale) {
		_scale = scale;
	}

	void ArcTransform::setRotation(glm::vec3 rotation) {
		_rotation = rotation;
	}

	const glm::mat4 ArcTransform::translate(GLfloat x, GLfloat y, GLfloat z) const {
		return glm::translate(glm::mat4(), glm::vec3(x, y, z));
	}

	const glm::mat4 ArcTransform::scale(GLfloat x, GLfloat y, GLfloat z) const {
		return glm::scale(glm::mat4(), glm::vec3(x, y, z));
	}

	const glm::mat4 ArcTransform::rotate(GLfloat x, GLfloat y, GLfloat z, GLfloat angle) const {
		return glm::rotate(glm::mat4(), angle, glm::vec3(x, y, z));
	}
}