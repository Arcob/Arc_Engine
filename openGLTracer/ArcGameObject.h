#pragma once

#include "commom.h"
#include "ArcTransform.h"

namespace Arc_Engine {
	
	class ArcBehaviour;
	class ArcRenderer;
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
		T* getComponent() {
			for (int i = 0; i < ArcBehaviourList.size(); i++) {
				auto temp = dynamic_cast<T*>(ArcBehaviourList[i].get());
				if (temp != nullptr) {
					return temp;
				}
			}
			return nullptr;
		}

		static void setGameObjectList(std::list<Arc_Engine::ArcGameObject>* list);

		//用到模板的函数声明和定义要放在一起否则会出现链接错误
		template<typename T>
		static std::vector<Arc_Engine::ArcGameObject*> findGameObjectsOfType() {
			std::vector<Arc_Engine::ArcGameObject*> result = std::vector<Arc_Engine::ArcGameObject*>();
			std::list<Arc_Engine::ArcGameObject>::iterator it;//start
			//std::cout << _gameObjectList->size() << std::endl;
			for (it = _gameObjectList->begin(); it != _gameObjectList->end(); ++it) {
				for (int i = 0; i < (it->behaviourListLength()); i++) {
					//(it->getBehaviourList())[i]->Start();
					//if (dynamic_cast<T*>(&*((it->getBehaviourList())[i])) != nullptr) {
					if (dynamic_cast<T*>(((it->getBehaviourList())[i]).get()) != nullptr) {
						Arc_Engine::ArcGameObject* temp = &*it;
						result.push_back(temp);
					}
				}
			}
			return result;
		}

	private:
		static std::list<Arc_Engine::ArcGameObject>* _gameObjectList;
		std::vector<std::shared_ptr<ArcBehaviour>> ArcBehaviourList;
		ArcTransform _transform;
		std::shared_ptr<ArcRenderer> _renderer = nullptr;
		std::string _name = "EmptyGameObject";
	};

}