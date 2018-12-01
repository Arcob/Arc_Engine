#include "stdafx.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Arc_Engine {

	static const float MaxVerticalAngle = 85.0f;

	Camera::Camera():
		_fieldOfView(50.0f),
		_nearPlane(0.01f),
		_farPlane(100.0f),
		_viewportAspectRatio(4.0f / 3.0f)
	{
	}

	float Camera::fieldOfView() const {
		return _fieldOfView;
	}

	void Camera::setFieldOfView(float fieldOfView) {
		assert(fieldOfView > 0.0f && fieldOfView < 180.0f);//assert效果是如果它的条件返回错误，则终止程序执行
		_fieldOfView = fieldOfView;
	}

	float Camera::nearPlane() const {
		return _nearPlane;
	}

	float Camera::farPlane() const {
		return _farPlane;
	}

	void Camera::setNearAndFarPlanes(float nearPlane, float farPlane) {
		assert(nearPlane > 0.0f);
		assert(farPlane > nearPlane);
		_nearPlane = nearPlane;
		_farPlane = farPlane;
	}

	float Camera::viewportAspectRatio() const {
		return _viewportAspectRatio;
	}

	void Camera::setViewportAspectRatio(float viewportAspectRatio) {
		assert(viewportAspectRatio > 0.0);
		_viewportAspectRatio = viewportAspectRatio;
	}

	glm::mat4 Camera::matrix() const {
		return projection() * view();
	}

	glm::mat4 Camera::projection() const {
		return glm::perspective(glm::radians(_fieldOfView), _viewportAspectRatio, _nearPlane, _farPlane);
	}

	glm::mat4 Camera::view() const {
		return (gameObject()->transform().rotationMatrix() * glm::translate(glm::mat4(), -gameObject()->transform().position()));
	}

}
