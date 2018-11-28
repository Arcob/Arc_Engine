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
		script->setGameObject(this);
	}

	const int ArcGameObject::behaviourListLength() const {
		return ArcBehaviourList.size();
	}

	const std::vector<std::shared_ptr<ArcBehaviour>> ArcGameObject::getBehaviourList() const {
		return ArcBehaviourList;
	}

}