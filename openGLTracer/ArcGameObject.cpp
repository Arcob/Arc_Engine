#include "ArcGameObject.h"

namespace Arc_Engine {

	/*ArcGameObject::ArcGameObject()
	{
	}


	ArcGameObject::~ArcGameObject()
	{
	}*/

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
}