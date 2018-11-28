#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include "ArcBehaviour.h"
#include "ArcRenderer.h"



namespace Arc_Engine {
	class ArcBehaviour;

	class ArcGameObject
	{
	public:
		ArcGameObject() = default;
		~ArcGameObject() = default;

		ArcRenderer* renderer = NULL;
		glm::mat4 transform;
		void attachScript(std::shared_ptr<Arc_Engine::ArcBehaviour> script);
		const int behaviourListLength() const;
		const std::vector<std::shared_ptr<Arc_Engine::ArcBehaviour>> getBehaviourList() const;

	private:
		std::vector<std::shared_ptr<ArcBehaviour>> ArcBehaviourList;
	};

}