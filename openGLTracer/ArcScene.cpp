#include "ArcScene.h"


namespace Arc_Engine {
	const std::shared_ptr<Arc_Engine::DirectionLight> ArcScene::light() const{
		return _light;
	}

	void ArcScene::setLight(std::shared_ptr<Arc_Engine::DirectionLight> light) {
		_light = light;
	}

	void ArcScene::addGameObject(std::shared_ptr<Arc_Engine::ArcGameObject> gameObject) {
		_sceneGameObjectObjects.push_back(gameObject);
	}

	std::vector<std::shared_ptr<ArcGameObject>> ArcScene::getGameObjectsInScene() {
		return _sceneGameObjectObjects; // 返回的是vector的复制
	}
}
