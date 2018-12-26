#pragma once
#include "common.h"

namespace Arc_Engine {

	class ArcShaderProgramCreater
	{
	public:
		static GLuint loadShaderAndCreateProgram(GLuint vertexShader, GLuint fragmentShader, std::string vertexShaderPath, std::string fragmentShaderPath);
	};

}

