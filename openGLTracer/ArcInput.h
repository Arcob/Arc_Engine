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
		//����һ������callback�Ļ���
		static void setWindowAndKeyboardCallback(GLFWwindow* window, GLFWkeyfun callBack);
		static void clearCache();
		static void swapTwoArray(bool * cache, bool* origin, const int size);

	private:
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static GLFWwindow* _window;
		static std::vector<int> _tempKeyPress;
		static std::vector<int> _tempKeyRelease;
		static std::vector<int> _tempKeyPressCache;  // ʹ�û����õ�ǰ֡�İ���������浽��һ֡
		static std::vector<int> _tempKeyReleaseCache;
		static bool _downHash[GLFW_KEY_LAST + 1];  // ��̬����
		static bool _downHashCache[GLFW_KEY_LAST + 1];  // ��̬����
	};

}

