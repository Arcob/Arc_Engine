#pragma once
#include <vector>
#include "ArcGameObject.h"

namespace Arc_Engine {

	class ArcScene
	{
	public:
		ArcScene() = default;
		~ArcScene() = default;
		std::vector<std::shared_ptr<ArcGameObject>> getGameObjectsInScene();
		void AwakeAllGameObjects();
		void StartAllGameObjects();
		void UpdateAllGameObjects();
	
	private:
		std::vector<std::shared_ptr<ArcGameObject>> _sceneGameObjectObjects;
	};
}

