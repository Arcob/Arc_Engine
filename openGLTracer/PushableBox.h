#pragma once

#include "common.h"
#include "ArcBehaviour.h"

class PushableBox :
	public Arc_Engine::ArcBehaviour
{
public:
	PushableBox() = default;
	~PushableBox() = default;
	void Start();
	void Update();
};

