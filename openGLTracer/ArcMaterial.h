#pragma once
#include "common.h"
#include "ArcGameObject.h"
#include "ArcApplication.h"

namespace Arc_Engine {

	class ArcMaterial
	{
	public:
		
		ArcMaterial::ArcMaterial(std::string vertexShaderPath, std::string fragmentShaderPath);
		static GLuint loadShaderAndCreateProgram(std::string vertexShaderPath, std::string fragmentShaderPath);
		const GLuint program();
		void setRenderFunction(RenderFunction function);
		void callRenderFunction(std::shared_ptr<Arc_Engine::ArcGameObject> gameObject, std::shared_ptr<Arc_Engine::ArcApplication> app);

	private:
		GLuint _programHandle;
		RenderFunction _renderFunction;
	};

}

