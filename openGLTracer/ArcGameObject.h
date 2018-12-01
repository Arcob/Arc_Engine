#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include "ArcBehaviour.h"
#include "ArcRenderer.h"
#include "ArcTransform.h"
#include <fstream>
#include <iostream>



namespace Arc_Engine {

	class ArcBehaviour;

	class ArcGameObject
	{
	public:
		ArcGameObject() = default;
		~ArcGameObject() = default;
		
		ArcRenderer* renderer = NULL;
		
		void attachScript(std::shared_ptr<Arc_Engine::ArcBehaviour> script);
		const int behaviourListLength() const;
		const std::vector<std::shared_ptr<Arc_Engine::ArcBehaviour>> getBehaviourList() const;
		const ArcTransform transform() const;
		ArcTransform* const transformPtr();
		void setTransfrom(ArcTransform transfrom);

	private:
		std::vector<std::shared_ptr<ArcBehaviour>> ArcBehaviourList;
		ArcTransform _transform;
	};

}