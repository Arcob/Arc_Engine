#include "ArcBehaviour.h"

namespace Arc_Engine {

	/*ArcBehaviour::ArcBehaviour()
	{
	}


	ArcBehaviour::~ArcBehaviour()
	{
	}*/

	std::shared_ptr<ArcGameObject> const ArcBehaviour::gameObject() const{
		return _gameObject;
	}
	
	void ArcBehaviour::Awake()
	{

	}

	void ArcBehaviour::Start()
	{

	}

	void ArcBehaviour::Update()
	{

	}


	void ArcBehaviour::setGameObject(std::shared_ptr<ArcGameObject> gameObject) {
		_gameObject = gameObject;
	}

}