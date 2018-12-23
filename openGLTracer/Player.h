#pragma once

#include "commom.h"
#include "MovableObject.h"

class Player :
	public MovableObject
{
public:
	Player()=default;
	~Player() = default;
	void Start();
	void Update();
	void judgeMove(glm::vec2 deltaPosition);

private:
	float _timeInterval = 0.6f;
	float _timer = 0;
	bool _canMove = true;
};

