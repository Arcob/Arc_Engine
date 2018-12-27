#pragma once
#include "common.h"

namespace Arc_Engine {

	class ArcShaderProgramCreater
	{
	public:
		static GLuint loadShaderAndCreateProgram(std::string vertexShaderPath, std::string fragmentShaderPath);
	};

}

