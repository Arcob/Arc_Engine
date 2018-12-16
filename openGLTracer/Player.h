#pragma once
#include "MovableObject.h"
#include "ArcInput.h"
#include "ArcTime.h"
#include <glm/glm.hpp>
#include "GameController.h"

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

