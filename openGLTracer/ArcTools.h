#pragma once
#include "common.h"
namespace Arc_Engine {

	class ArcTools
	{
	public:
		static std::string getCurrentPath() {
			char buf[80];
			_getcwd(buf, sizeof(buf)); //将当前工作目录的绝对路径复制到参数buffer所指的内存空间中
			std::string path1 = std::string(buf);
			std::size_t found = path1.find_last_of("/\\");
			return path1.substr(0, found);
		}
	};
}

