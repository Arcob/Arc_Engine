#pragma once
#include "ArcBehaviour.h"
#include <iostream>

class PushableBox :
	public Arc_Engine::ArcBehaviour
{
public:
	PushableBox() = default;
	~PushableBox() = default;
	void Start();
	void Update();
};

