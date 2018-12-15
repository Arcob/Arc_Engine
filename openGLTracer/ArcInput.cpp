#include "ArcInput.h"

namespace Arc_Engine {

	GLFWwindow* ArcInput::_window = nullptr;
	std::vector<int> ArcInput::_tempKeyPress = std::vector<int>();
	std::vector<int> ArcInput::_tempKeyRelease = std::vector<int>();
	std::vector<int> ArcInput::_tempKeyPressCache = std::vector<int>();
	std::vector<int> ArcInput::_tempKeyReleaseCache = std::vector<int>();
	bool ArcInput::_downHash[] = { false };
	bool ArcInput::_downHashCache[] = { false };
	//bool* ArcInput::downHash[] = new bool[GLFW.GLFW_KEY_LAST + 1];

	void ArcInput::setWindowAndKeyboardCallback(GLFWwindow* window) {
		_window = window;
		glfwSetKeyCallback(_window, key_callback);
	}

	void ArcInput::setWindowAndKeyboardCallback(GLFWwindow* window, GLFWkeyfun callBack) {
		_window = window;
		glfwSetKeyCallback(_window, callBack);
	}

	void ArcInput::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		//std::cout << key << std::endl;
		if (action == GLFW_PRESS) {
			_tempKeyPress.push_back(key);
			ArcInput::_downHash[key] = true;
		}
		if (action == GLFW_RELEASE) {
			_tempKeyRelease.push_back(key);
			ArcInput::_downHash[key] = false;
		}
	}

	void ArcInput::clearCache() {
		//swapTwoArray(_downHashCache, _downHash, GLFW_KEY_LAST + 1);
		memcpy(_downHashCache, _downHash, (GLFW_KEY_LAST + 1));
		_tempKeyPressCache.swap(_tempKeyPress);
		_tempKeyReleaseCache.swap(_tempKeyRelease);
		_tempKeyPress.clear();
		_tempKeyRelease.clear();
	}

	bool ArcInput::getKeyDown(const int key) {
		for (int i = 0; i < _tempKeyPressCache.size(); i++) {
			if (_tempKeyPressCache[i] == key) {
				return true;
			}
		}
		return false;
	}
	
	bool ArcInput::getKey(const int key) {
		/*for (int i = 0; i < _tempKeyRepeatCache.size(); i++) {
			if (_tempKeyRepeatCache[i] == key) {
				return true;
			}
		}
		return false;*/
		return ArcInput::_downHashCache[key];
	}

	bool ArcInput::getKeyUp(const int key) {
		for (int i = 0; i < _tempKeyReleaseCache.size(); i++) {
			if (_tempKeyReleaseCache[i] == key) {
				return true;
			}
		}
		return false;
	}

	void ArcInput::swapTwoArray(bool * cache, bool* origin, const int size) {
		for (int i = 0; i < size; i++) {
			cache[i] = origin[i];
			//origin[i] = false;
		}
	}

}
