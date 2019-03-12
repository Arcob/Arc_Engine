#pragma once
#include "common.h"
#include "ArcGameObject.h"
#include "ArcApplication.h"

namespace Arc_Engine {

	const std::string shader_path = "\\shaders";
	const std::string depth_vert_shader_path = "\\shadowShader\\depth_vert.vert";
	const std::string depth_frag_shader_path = "\\shadowShader\\depth_frag.frag";

	class ArcMaterial
	{
	public:
		
		ArcMaterial::ArcMaterial(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		static GLuint loadShaderAndCreateProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		static GLuint loadShadowProgram();
		const GLuint program();
		void setRenderFunction(RenderFunction function);
		void callRenderFunction(GLuint program, std::shared_ptr<Arc_Engine::ArcGameObject> gameObject, std::shared_ptr<Arc_Engine::ArcApplication> app);

	private:
		static GLuint _shadowProgram;
		GLuint _programHandle;
		RenderFunction _renderFunction;
	};

}

