#include "ArcScene.h"


namespace Arc_Engine {
	const std::shared_ptr<Arc_Engine::DirectionLight> ArcScene::light() const{
		return _light;
	}

	const GLuint ArcScene::depthMap() const {
		return _depthMap;
	}

	const GLuint ArcScene::depthMapFBO() const {
		return _depthMapFBO;
	}

	void ArcScene::setLight(std::shared_ptr<Arc_Engine::DirectionLight> light) {
		_light = light;
	}

	void ArcScene::addGameObject(std::shared_ptr<Arc_Engine::ArcGameObject> gameObject) {
		_sceneGameObjectObjects.push_back(std::move(gameObject));
	}

	std::vector<std::shared_ptr<ArcGameObject>> ArcScene::getGameObjectsInScene() {
		return _sceneGameObjectObjects; // 返回的是vector的复制
	}

	void ArcScene::enableShadow() {
		Arc_Engine::ArcTextureLoader::createDepthMap(&_depthMap);
		createShadowBuffer(&_depthMapFBO, _depthMap);
	}

	void ArcScene::createShadowBuffer(GLuint* depthMapFBO, GLuint depthMap) {
		glGenFramebuffers(1, depthMapFBO);

		glBindFramebuffer(GL_FRAMEBUFFER, *depthMapFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}
