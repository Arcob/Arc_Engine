#pragma once
#include <glm/glm.hpp>
#include "ArcBehaviour.h"
#include "ArcGameObject.h"
#include <fstream>
#include <iostream>

namespace Arc_Engine {
	class Camera :
		public ArcBehaviour
	{
	public:
		Camera();

		float fieldOfView() const;
		void setFieldOfView(float fieldOfView);

		float nearPlane() const;
		float farPlane() const;
		void setNearAndFarPlanes(float nearPlane, float farPlane);

		float viewportAspectRatio() const;
		void setViewportAspectRatio(float viewportAspectRatio);

		glm::mat4 matrix() const;
		glm::mat4 projection() const;
		glm::mat4 view() const;

	private:
		float _fieldOfView;
		float _nearPlane;
		float _farPlane;
		float _viewportAspectRatio;

	};
}


