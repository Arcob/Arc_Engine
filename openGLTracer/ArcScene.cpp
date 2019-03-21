#include "ArcScene.h"
#include "DriverSetting.h"


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

	const GLuint ArcScene::postEffectFBO() const {
		return _postEffectMapFBO;
	}

	const GLuint ArcScene::postEffectMap() const {
		return _postEffectMap;
	}

	const GLuint ArcScene::gBufferMap() const {
		return _gBufferMap;
	}

	const GLuint ArcScene::gBufferMapFBO() const {
		return _gBufferMapFBO;
	}

	const GLuint ArcScene::gPositionMap() const {
		return _positionMap;
	}

	void ArcScene::enableGBuffer() {
		Arc_Engine::ArcTextureLoader::createDefaultRGBA16FMap(&_gBufferMap);
		createGBuffer(&_gBufferMapFBO, _gBufferMap);
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

	void ArcScene::enablePostEffect() {
		//Arc_Engine::ArcTextureLoader::createPostEffectMap(&_postEffectMap);
		Arc_Engine::ArcTextureLoader::createDefaultRGBA16FMap(&_postEffectMap);
		createPostEffectBuffer(&_postEffectMapFBO, _postEffectMap);
	}

	void ArcScene::createShadowBuffer(GLuint* depthMapFBO, GLuint depthMap) {
		glGenFramebuffers(1, depthMapFBO);
		glBindFramebuffer(GL_FRAMEBUFFER, *depthMapFBO);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void ArcScene::createGBuffer(GLuint* gBufferFBO, GLuint gBufferMap) {
		glGenFramebuffers(1, gBufferFBO);
		glBindFramebuffer(GL_FRAMEBUFFER, *gBufferFBO);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gBufferMap, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	
	void ArcScene::createPostEffectBuffer(GLuint* postEffectMapFBO, GLuint postEffectMap) {
		glGenFramebuffers(1, postEffectMapFBO);
		glBindFramebuffer(GL_FRAMEBUFFER, *postEffectMapFBO);

		//color
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, postEffectMap, 0);

		//创建渲染缓冲对象存储深度信息
		GLuint rbo; // render buffer object
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH * ANTI_AILASING_MULTY_TIME, HEIGHT * ANTI_AILASING_MULTY_TIME);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

		//gbuffer
		Arc_Engine::ArcTextureLoader::createDefaultRGBA16FMap(&_gBufferMap);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, _gBufferMap, 0);

		Arc_Engine::ArcTextureLoader::createDefaultRGBA16FMap(&_positionMap);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, _positionMap, 0);

		GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
		glDrawBuffers(3, drawBuffers);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}
