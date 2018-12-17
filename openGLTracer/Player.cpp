#include "Player.h"



/*Player::Player()
{
}


Player::~Player()
{
}*/

void Player::Start() {
	MovableObject::Start();
}

void Player::Update() {
	MovableObject::Update();
	if (_canMove)
	{
		if (Arc_Engine::ArcInput::getKey('W'))
		{
			judgeMove(glm::vec2(0.0f, 1.0f));
		}
		else if (Arc_Engine::ArcInput::getKey('S'))
		{
			judgeMove(glm::vec2(0.0f, -1.0f));
		}
		else if (Arc_Engine::ArcInput::getKey('D'))
		{
			judgeMove(glm::vec2(-1.0f, 0.0f));
		}
		else if (Arc_Engine::ArcInput::getKey('A'))
		{
			judgeMove(glm::vec2(1.0f, 0.0f));
		}
	}
	if (!_canMove)
	{
		_timer += Arc_Engine::ArcTime::deltaTime();
		if (_timer > _timeInterval)
		{
			_timer = 0.0f;
			_canMove = true;
		}
	}
}

void Player::judgeMove(glm::vec2 deltaPosition) {
	/*glm::vec2 target = coord() + deltaPosition;
	if (!GameController::instance->isWall(target)) {
		if (GameController::instance->isMovableCube(target))
		{
			glm::vec2 doubleTarget = target + deltaPosition;
			if (!GameController::instance->isWall(doubleTarget) && !GameController::instance->isMovableCube(doubleTarget))
			{
				setTargetCoord(target);
				//GameController::instance->findMovableCube(target).setTargetCoord(doubleTarget);
				_canMove = false;
			}
			return;
		}
		setTargetCoord(target);
		_canMove = false;
	}*/
	glm::vec2 target = coord() + deltaPosition;
	if (!GameController::instance->isWall(target)) {
		setTargetCoord(target);
		_canMove = false;
	}
}
