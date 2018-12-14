#pragma once

#include <GLFW/glfw3.h>
#include <vector>

#include <fstream>
#include <iostream>

namespace Arc_Engine {

	static class ArcInput
	{
	public:
		static bool getKeyDown(const int key);
		static bool getKey(const int key);
		static bool getKeyUp(const int key);
		static void setWindowAndKeyboardCallback(GLFWwindow* window);
		static void setWindowAndKeyboardCallback(GLFWwindow* window, GLFWkeyfun callBack);
		//static void setKeyboardCallback();
		static void clearCache();

	private:
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static GLFWwindow* _window;
		static std::vector<int> _tempKeyPress;
		static std::vector<int> _tempKeyRelease;
		static std::vector<int> _tempKeyRepeat;
	};

}

