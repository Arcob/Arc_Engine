#include "ArcApplication.h"

namespace Arc_Engine {

	ArcApplication::ArcApplication(std::shared_ptr<class ArcScene> inputScene) :
		_isRunning(true), _scene(std::move(inputScene))
	{
	}

	void registerScene() {

	}
}
