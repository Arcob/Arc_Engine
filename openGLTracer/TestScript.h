#pragma once

#include "common.h"
#include "ArcBehaviour.h"

class TestScript :
	public Arc_Engine::ArcBehaviour
{
public:
	TestScript() = default;
	~TestScript() = default;
	void Start();
	void Update();
};

