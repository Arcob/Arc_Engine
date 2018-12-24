#include "ArcApplication.h"

namespace Arc_Engine {

	ArcApplication::ArcApplication(std::shared_ptr<class ArcScene> inputScene) :
		_isRunning(true), _scene(std::move(inputScene))
	{
	}

	void ArcApplication::registerSelf() {

	}

	void ArcApplication::setMainCamera(std::shared_ptr<class Arc_Engine::Camera> camera) {
		_mainCamera = camera;
	}

	std::shared_ptr<class ArcScene> ArcApplication::scene() {
		return _scene;
	}
}
