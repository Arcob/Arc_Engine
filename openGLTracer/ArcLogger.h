#pragma once

#include <fstream>
#include <iostream>

namespace Arc_Engine {

	static class ArcLogger
	{
	public:
		template <typename T>
		static void log(const T info) {
			std::cout << info << std::endl;
		}
	};
	
}

