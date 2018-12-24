#pragma once
#include "common.h"

namespace Arc_Engine {
	class DirectionLight
	{
	public:
		DirectionLight();
		~DirectionLight() = default;
		const glm::vec3& direction() const;
		const glm::vec3& ambient() const;
		const glm::vec3& diffuse() const;
		void setDirection(const glm::vec3& direction);
		void setAmbient(const glm::vec3& ambient);
		void setDiffuse(const glm::vec3& diffuse);


	private:
		glm::vec3 _direction; // 方向光源
		glm::vec3 _ambient;
		glm::vec3 _diffuse;
	};
}

