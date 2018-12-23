#pragma once

#include "commom.h"
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

