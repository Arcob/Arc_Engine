#pragma once
#include "MovableObject.h"
class MovableCube :
	public MovableObject
{
public:
	MovableCube() = default;
	~MovableCube() = default;
	void Start();
	void Update();
};

