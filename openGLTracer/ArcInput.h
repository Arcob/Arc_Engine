#pragma once
#include "commom.h"

namespace Arc_Engine {

	static class ArcInput
	{
	public:
		static bool getKeyDown(const int key);
		static bool getKey(const int key);
		static bool getKeyUp(const int key);
		static void setWindowAndKeyboardCallback(GLFWwindow* window);
		//给你一个重载callback的机会
		static void setWindowAndKeyboardCallback(GLFWwindow* window, GLFWkeyfun callBack);
		static void clearCache();
		static void swapTwoArray(bool * cache, bool* origin, const int size);

	private:
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static GLFWwindow* _window;
		static std::vector<int> _tempKeyPress;
		static std::vector<int> _tempKeyRelease;
		static std::vector<int> _tempKeyPressCache;  // 使用缓存让当前帧的按下情况缓存到下一帧
		static std::vector<int> _tempKeyReleaseCache;
		static bool _downHash[GLFW_KEY_LAST + 1];  // 静态数组
		static bool _downHashCache[GLFW_KEY_LAST + 1];  // 静态数组
	};

}

