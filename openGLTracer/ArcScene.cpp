#include "ArcScene.h"


namespace Arc_Engine {
	const std::shared_ptr<Arc_Engine::DirectionLight> ArcScene::light() const{
		return _light;
	}

	const GLuint ArcScene::shadowTexture() const {
		return _shadowTexture;
	}

	void ArcScene::setShadowTexture(GLuint shadowTexture) {
		_shadowTexture = shadowTexture;
	}

	void ArcScene::setLight(std::shared_ptr<Arc_Engine::DirectionLight> light) {
		_light = light;
	}

	void ArcScene::addGameObject(std::shared_ptr<Arc_Engine::ArcGameObject> gameObject) {
		_sceneGameObjectObjects.push_back(std::move(gameObject));
	}

	std::vector<std::shared_ptr<ArcGameObject>> ArcScene::getGameObjectsInScene() {
		return _sceneGameObjectObjects; // ���ص���vector�ĸ���
	}
}
