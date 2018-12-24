#pragma once
#include "common.h"

namespace Arc_Engine {

	class ArcApplication
	{
	public:
		ArcApplication(std::shared_ptr<class ArcScene> inputScene);
		virtual ~ArcApplication() = default;
		std::shared_ptr<class ArcScene> scene();
		void registerSelf();

	private:
		bool _isRunning = true;
		std::shared_ptr<class ArcScene> _scene;
	};
	
}

