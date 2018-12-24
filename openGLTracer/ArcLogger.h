#pragma once

#include "common.h"

namespace Arc_Engine {

	class ArcLogger
	{
	public:
		template <typename T>
		static void log(const T info) {
			std::cout << info << std::endl;
		}
	};
	
}

