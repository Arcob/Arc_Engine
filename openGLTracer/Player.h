#pragma once

#include "common.h"
#include "MovableObject.h"
#include "ArcInput.h"
#include "ArcTime.h"
#include "ArcLogger.h"
#include "GameController.h"

class GameController;

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

