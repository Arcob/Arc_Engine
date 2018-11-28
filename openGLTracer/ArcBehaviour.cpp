#include "ArcBehaviour.h"

namespace Arc_Engine {

	ArcBehaviour::ArcBehaviour()
	{
	}


	ArcBehaviour::~ArcBehaviour()
	{
	}

	const ArcGameObject* ArcBehaviour::gameObject() const {
		return _gameObject;
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