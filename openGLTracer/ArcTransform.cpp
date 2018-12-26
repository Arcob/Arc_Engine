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

	void ArcTransform::translate(glm::vec3 offset) {
		_position += offset;
	}

	void ArcTransform::rotate(glm::vec3 eularAngle) {
		rotate(eularAngle.x, eularAngle.y, eularAngle.z);
	}

	void ArcTransform::lookAt(glm::vec3 target) {  // 这个lookat的Up
		if (target == _position) {
			return;
		}
		glm::vec3 direction = glm::normalize(target - _position);
		float angleX = glm::radians(asinf(-direction.y));
		float angleY = -glm::radians(atan2f(-direction.x, -direction.z));
		normalizeRotation();
	}

	void ArcTransform::rotate(float rightAngle, float upAngle, float forwardAngle) {
		//glm::vec3 tempRotation;
		_rotation = glm::vec3(_rotation.x + rightAngle, _rotation.y + upAngle, _rotation.z + forwardAngle);
		normalizeRotation();
	}
	
	glm::vec3 ArcTransform::forward() const {
		glm::vec4 forward = glm::inverse(ArcTransform::rotationMatrix()) * glm::vec4(0, 0, -1, 1);
		return glm::vec3(forward);
	}
	
	glm::vec3 ArcTransform::right() const {
		glm::vec4 right = glm::inverse(ArcTransform::rotationMatrix()) * glm::vec4(1, 0, 0, 1);
		return glm::vec3(right);
	}
	
	glm::vec3 ArcTransform::up() const {
		glm::vec4 right = glm::inverse(ArcTransform::rotationMatrix()) * glm::vec4(0, 1, 0, 1);
		return glm::vec3(right);
	}

	void ArcTransform::normalizeRotation() {
		float angleX = _rotation.x;
		float angleY = _rotation.y;
		float angleZ = _rotation.z;

		angleX = fmodf(angleX, 360.0f); //fmodf可能返回负数，所以之后还得加360.。。
		angleY = fmodf(angleY, 360.0f);
		angleZ = fmodf(angleZ, 360.0f);

		if (angleX < 0.0f)
			angleX += 360.0f;
		if (angleY < 0.0f)
			angleY += 360.0f;
		if (angleZ < 0.0f)
			angleZ += 360.0f;

		_rotation = glm::vec3(angleX, angleY, angleZ);
	}
}
