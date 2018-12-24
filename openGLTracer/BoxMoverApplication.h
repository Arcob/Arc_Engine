#pragma once
#include "ArcApplication.h"

class BoxMoverApplication :
	public Arc_Engine::ArcApplication
{
public:
	BoxMoverApplication(std::shared_ptr<class Arc_Engine::ArcScene> inputScene);
	~BoxMoverApplication();
};

