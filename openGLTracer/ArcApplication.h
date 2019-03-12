#pragma once
#include "common.h"
#include "Camera.h"

namespace Arc_Engine {
	
	class ArcApplication
	{
	public:
		ArcApplication(std::shared_ptr<class ArcScene> inputScene, GLuint WIDTH, GLuint HEIGHT);
		virtual ~ArcApplication() = default;
		std::shared_ptr<class ArcScene> scene();
		void setMainCamera(std::shared_ptr<class Arc_Engine::Camera> camera);
		std::shared_ptr<Arc_Engine::Camera> mainCamera();
		const std::string name();
		void setName(std::string name);
		void registerSelf();
		const GLuint width();
		const GLuint height();
		//const GLuint WIDTH = 800, HEIGHT = 600;

	private:
		GLuint _width = 800;
		GLuint _height = 600;
		std::shared_ptr<Arc_Engine::Camera> _mainCamera;
		std::string _name;
		bool _isRunning = true;
		std::shared_ptr<class ArcScene> _scene;
	};
	
	typedef void(*RenderFunction)(GLuint program, std::shared_ptr<Arc_Engine::ArcGameObject>, std::shared_ptr<Arc_Engine::ArcApplication>);

}

