#include "ArcGameObject.h"
#include "ArcBehaviour.h"

namespace Arc_Engine {

	/*ArcGameObject::ArcGameObject()
	{
	}


	ArcGameObject::~ArcGameObject()
	{
	}*/

	std::list<Arc_Engine::ArcGameObject>* ArcGameObject::_gameObjectList = nullptr;

	void Arc_Engine::ArcGameObject::attachScript(std::shared_ptr<Arc_Engine::ArcBehaviour> script) {
		ArcBehaviourList.push_back(script);
		//std::cout << " a: " << this->behaviourListLength() << std::endl;
		script->setGameObject(this);
		//std::cout << " b: " << script->gameObject()->behaviourListLength() << std::endl;
	}

	const int ArcGameObject::behaviourListLength() const {
		return ArcBehaviourList.size();
	}

	const std::vector<std::shared_ptr<ArcBehaviour>> ArcGameObject::getBehaviourList() const {
		return ArcBehaviourList;
	}

	const ArcTransform ArcGameObject::transform() const {
		return _transform;
	}

	ArcTransform* const ArcGameObject::transformPtr(){
		return &_transform;
	}

	void ArcGameObject::setTransfrom(ArcTransform transform) {
		_transform = transform;
	}

	void ArcGameObject::setName(std::string name) {
		_name = name;
	}

	const std::string ArcGameObject::name() const {
		return _name;
	}

	void ArcGameObject::setRenderer(std::shared_ptr<ArcRenderer> renderer) {
		_renderer = renderer;
	}

	const std::shared_ptr<ArcRenderer> ArcGameObject::renderer() const {
		return _renderer;
	}

	void ArcGameObject::setGameObjectList(std::list<Arc_Engine::ArcGameObject>* list) {
		_gameObjectList = list;
	}

	/*template<typename T>
	T* ArcGameObject::getAComponent() {
		for (int i = 0; i < ArcBehaviourList.size(); i++) {
			if (dynamic_cast<T*>(ArcBehaviourList[i].get()) != nullptr) {
				return ArcBehaviourList[i].get();
			}
		}
		return NULL;
	}*/
}