#pragma once
#include <memory>
#include "ArcScene.h"

namespace Arc_Engine {

	class ArcApplication
	{
	public:
		ArcApplication(std::shared_ptr<class ArcScene> inputScene);
		virtual ~ArcApplication() = default;
		void registerScene();

	private:
		bool _isRunning = true;
		std::shared_ptr<class ArcScene> _scene;
	};
	
}

