#pragma once
#include "commom.h"

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

