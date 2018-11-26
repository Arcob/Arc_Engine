#pragma once

#include "ArcBehaviour.h"
#include <iostream>

class TestScript :
	public ArcBehaviour
{
public:
	TestScript() = default;
	~TestScript() = default;
	void Start();
	void Update();
};

