#include "LightBundle.h"


namespace Arc_Engine {
	DirectionLight::DirectionLight():
		_position(0.0f, 0.0f, 0.0f),
		_direction(0.0f,0.0f,0.0f),
		_ambient(0.0f, 0.0f, 0.0f),
		_diffuse(0.0f, 0.0f, 0.0f)
	{
	}

	const glm::vec3& DirectionLight::position() const {
		return _position;
	}

	const glm::vec3& DirectionLight::direction() const {
		return _direction;
	}

	const glm::vec3& DirectionLight::ambient() const {
		return _ambient;
	}

	const glm::vec3& DirectionLight::diffuse() const {
		return _diffuse;
	}

	void DirectionLight::setPosition(const glm::vec3& position) {
		_position = position;
	}

	void DirectionLight::setDirection(const glm::vec3& direction) {
		_direction = direction;
	}

	void DirectionLight::setAmbient(const glm::vec3& ambient) {
		_ambient = ambient;
	}

	void DirectionLight::setDiffuse(const glm::vec3& diffuse) {
		_diffuse = diffuse;
	}

	glm::mat4 DirectionLight::lightProjection() {
		GLfloat near_plane = 1.0f, far_plane = 7.5f; // nearplane∫Õfarplaneœ»–¥À¿
		return glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
	}

	glm::mat4 DirectionLight::lightView() {
		return glm::lookAt(_position, _position + _direction, glm::vec3(0.0, 1.0, 0.0));
	}
}
