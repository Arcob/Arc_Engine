#include "ArcInput.h"

namespace Arc_Engine {

	GLFWwindow* ArcInput::_window = nullptr;
	std::vector<int> ArcInput::_tempKeyPress = std::vector<int>();//glfw的keycode里0不代表任何key
	std::vector<int> ArcInput::_tempKeyRelease = std::vector<int>();
	std::vector<int> ArcInput::_tempKeyRepeat = std::vector<int>();

	void ArcInput::setWindowAndKeyboardCallback(GLFWwindow* window) {
		_window = window;
		//std::cout << _window << std::endl;
		glfwSetKeyCallback(_window, key_callback);
	}

	void ArcInput::setWindowAndKeyboardCallback(GLFWwindow* window, GLFWkeyfun callBack) {
		_window = window;
		//std::cout << _window << std::endl;
		glfwSetKeyCallback(_window, callBack);
	}

	/*void ArcInput::setKeyboardCallback() {
		glfwSetKeyCallback(_window, key_callback);
	}*/

	void ArcInput::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		//std::cout << key << std::endl;
		if (action == GLFW_PRESS) {
			_tempKeyPress.push_back(key);
		}
		if (action == GLFW_RELEASE) {
			_tempKeyRelease.push_back(key);
		}
		if (action == GLFW_REPEAT) {
			_tempKeyRepeat.push_back(key);
		}
	}
	void ArcInput::clearCache() {
		_tempKeyPress.clear();
		_tempKeyRelease.clear();
		_tempKeyRepeat.clear();
	}

	bool ArcInput::getKeyDown(const int key) {
		for (int i = 0; i < _tempKeyPress.size(); i++) {
			if (_tempKeyPress[i] == key) {
				return true;
			}
		}
		return false;
	}
	
	bool ArcInput::getKey(const int key) {
		for (int i = 0; i < _tempKeyRepeat.size(); i++) {
			if (_tempKeyRepeat[i] == key) {
				return true;
			}
		}
		return false;
	}

	bool ArcInput::getKeyUp(const int key) {
		for (int i = 0; i < _tempKeyRelease.size(); i++) {
			if (_tempKeyRelease[i] == key) {
				return true;
			}
		}
		return false;
	}

}
