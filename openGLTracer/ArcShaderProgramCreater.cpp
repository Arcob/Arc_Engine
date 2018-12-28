#include "ArcShaderProgramCreater.h"

namespace Arc_Engine {

	GLuint ArcShaderProgramCreater::loadShaderAndCreateProgram(std::string vertexShaderPath, std::string fragmentShaderPath) {
		std::ifstream v(vertexShaderPath);
		std::string vertBuffer((std::istreambuf_iterator<char>(v)), std::istreambuf_iterator<char>());
		std::ifstream f(fragmentShaderPath);
		std::string fragBuffer((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());

		const GLchar* vertCharArray = vertBuffer.c_str();
		const GLchar* fragCharArray = fragBuffer.c_str();
		const GLint vertCharArrayLength = vertBuffer.size();
		const GLint fragCharArrayLength = fragBuffer.size();
		
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(vertexShader, 1, &vertCharArray, &vertCharArrayLength);
		glShaderSource(fragmentShader, 1, &fragCharArray, &fragCharArrayLength);

		glCompileShader(vertexShader);
		glCompileShader(fragmentShader);

		GLuint result = glCreateProgram();
		//ArcApplication::setShaderProgram(glCreateProgram());
		//std::cout << ArcApplication::shaderProgram() << std::endl;
		glAttachShader(result, vertexShader);
		glAttachShader(result, fragmentShader);

		glLinkProgram(result);
		return result;
	}

}
