#pragma once
#include "commom.h"

namespace Arc_Engine {
	class DirectionLight;
	class ArcGameObject;

	class ArcScene: public std::enable_shared_from_this<ArcScene>
	{
	public:
		std::vector<std::shared_ptr<ArcGameObject>> getGameObjectsInScene();
		const std::shared_ptr<Arc_Engine::DirectionLight> light() const;
		void setLight(std::shared_ptr<Arc_Engine::DirectionLight> light); //之后把light改成基类？
		void addGameObject(std::shared_ptr<Arc_Engine::ArcGameObject> gameObject);

	private:
		std::vector<std::shared_ptr<ArcGameObject>> _sceneGameObjectObjects;
		std::shared_ptr<Arc_Engine::DirectionLight> _light;
	};
}

