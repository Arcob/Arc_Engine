#include "ArcApplication.h"

namespace Arc_Engine {

	ArcApplication::ArcApplication(std::shared_ptr<class ArcScene> inputScene) :
		_isRunning(true), _scene(std::move(inputScene))
	{
	}

	void ArcApplication::registerSelf() {

	}

	std::shared_ptr<class ArcScene> ArcApplication::scene() {
		return _scene;
	}
}
