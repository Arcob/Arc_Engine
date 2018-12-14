#include "ArcBehaviour.h"

namespace Arc_Engine {

	/*ArcBehaviour::ArcBehaviour()
	{
	}


	ArcBehaviour::~ArcBehaviour()
	{
	}*/

	ArcGameObject* const ArcBehaviour::gameObject() const{
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


	void ArcBehaviour::setGameObject(ArcGameObject* gameObject) {
		_gameObject = gameObject;
	}

}