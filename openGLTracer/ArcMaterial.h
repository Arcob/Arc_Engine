#pragma once
#include "common.h"

namespace Arc_Engine {

	class ArcMaterial
	{
	public:
		ArcMaterial::ArcMaterial(std::string vertexShaderPath, std::string fragmentShaderPath);
		static GLuint loadShaderAndCreateProgram(std::string vertexShaderPath, std::string fragmentShaderPath);
		const GLuint program();

	private:
		GLuint _programHandle;
	};

}

