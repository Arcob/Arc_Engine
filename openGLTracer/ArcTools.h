#pragma once
#include "common.h"
namespace Arc_Engine {

	class ArcTools
	{
	public:
		static std::string getCurrentPath() {
			char buf[80];
			_getcwd(buf, sizeof(buf)); //����ǰ����Ŀ¼�ľ���·�����Ƶ�����buffer��ָ���ڴ�ռ���
			std::string path1 = std::string(buf);
			std::size_t found = path1.find_last_of("/\\");
			return path1.substr(0, found);
		}
	};
}

