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
}
