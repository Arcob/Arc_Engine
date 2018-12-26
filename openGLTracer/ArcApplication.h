#pragma once
#include "common.h"
#include "Camera.h"

namespace Arc_Engine {

	class ArcApplication
	{
	public:
		ArcApplication(std::shared_ptr<class ArcScene> inputScene);
		virtual ~ArcApplication() = default;
		std::shared_ptr<class ArcScene> scene();
		void setMainCamera(std::shared_ptr<class Arc_Engine::Camera> camera);
		std::shared_ptr<Arc_Engine::Camera> mainCamera();
		const std::string name();
		void setName(std::string name);
		void registerSelf();

	private:
		std::shared_ptr<Arc_Engine::Camera> _mainCamera;
		std::string _name;
		bool _isRunning = true;
		std::shared_ptr<class ArcScene> _scene;
	};
	
}

