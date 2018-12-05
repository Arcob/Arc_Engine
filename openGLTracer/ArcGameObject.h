#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <memory>
#include "ArcBehaviour.h"
#include "ArcRenderer.h"
#include "ArcTransform.h"
#include <fstream>
#include <iostream>



namespace Arc_Engine {
	
	class ArcBehaviour;
	class Camera;
	class ArcGameObject
	{
	public:
		ArcGameObject() = default;
		~ArcGameObject() = default;
		
		void attachScript(std::shared_ptr<Arc_Engine::ArcBehaviour> script);
		const int behaviourListLength() const;
		const std::vector<std::shared_ptr<Arc_Engine::ArcBehaviour>> getBehaviourList() const;
		const ArcTransform transform() const;
		ArcTransform* const transformPtr();
		void setTransfrom(ArcTransform transfrom);
		void setName(std::string name);
		const std::string name() const;
		void setRenderer(std::shared_ptr<ArcRenderer> renderer);
		const std::shared_ptr<ArcRenderer> renderer() const;

		template<typename T>
		T* getAComponent() {
			for (int i = 0; i < ArcBehaviourList.size(); i++) {
				auto temp = dynamic_cast<T*>(ArcBehaviourList[i].get());
				if (temp != nullptr) {
					return temp;
				}
			}
			return nullptr;
		}

	private:
		std::vector<std::shared_ptr<ArcBehaviour>> ArcBehaviourList;
		ArcTransform _transform;
		std::shared_ptr<ArcRenderer> _renderer = nullptr;
		std::string _name = "EmptyGameObject";
	};

}