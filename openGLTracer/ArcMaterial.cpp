#include "ArcMaterial.h"
#include "ArcTools.h"

namespace Arc_Engine {

	GLuint ArcMaterial::_shadowProgram = -1; //GLunit不包含-1，此处实际是最大值

	ArcMaterial::ArcMaterial(std::string vertexShaderPath, std::string fragmentShaderPath):
		_programHandle(loadShaderAndCreateProgram(vertexShaderPath, fragmentShaderPath)), _renderFunction(nullptr)
	{
		//_programHandle = loadShaderAndCreateProgram(vertexShaderPath, fragmentShaderPath);
	}

	const GLuint ArcMaterial::program() {
		return _programHandle;
	}

	void ArcMaterial::setRenderFunction(RenderFunction function) {
		_renderFunction = function;
	}

	void ArcMaterial::callRenderFunction(GLuint program, std::shared_ptr<Arc_Engine::ArcGameObject> gameObject, std::shared_ptr<Arc_Engine::ArcApplication> app) {
		_renderFunction(program, gameObject, app);
	}

	GLuint ArcMaterial::loadShaderAndCreateProgram(std::string vertexShaderPath, std::string fragmentShaderPath) {
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

	GLuint ArcMaterial::loadShadowProgram() {
		if (_shadowProgram == -1) {
			std::string currentPath = ArcTools::getCurrentPath();
			_shadowProgram = loadShaderAndCreateProgram(currentPath + shader_path + depth_vert_shader_path, currentPath + shader_path + depth_frag_shader_path);
		}
		return _shadowProgram;
	}
}
