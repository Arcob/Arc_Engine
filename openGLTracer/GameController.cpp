#include "GameController.h"
#include "ArcInput.h"
#include "ArcLogger.h"
#include "Player.h"

GameController* GameController::instance = nullptr;

void GameController::Awake()
{
	instance = this;
	//Arc_Engine::ArcLogger::log("GameController Awake");
}

void GameController::Start()
{
	_movableCubeArray = std::vector<MovableCube*>();
	auto _movableCubeGameObjectArray = Arc_Engine::ArcGameObject::findGameObjectsOfType<MovableCube>();
	for (int i = 0; i < _movableCubeGameObjectArray.size(); i++) {
		_movableCubeArray.push_back(_movableCubeGameObjectArray[i]->getComponent<MovableCube>());
	}
	_player = Arc_Engine::ArcGameObject::findGameObjectsOfType<Player>()[0]->getComponent<Player>();
}

void GameController::Update()
{
	if (Arc_Engine::ArcInput::getKeyDown(32)) { //GLFW_KEY_SPACE   32
		resetToOrigin();
	}
	if (!win && judgeWin())
	{
		win = true;
		Arc_Engine::ArcLogger::log("you win");
	}
}

const float GameController::moveSpeed() const{
	return _moveSpeed;
}

bool GameController::isWall(int x, int y) {
	return map[y][x] == 1 ? true : false;
}

bool GameController::isTarget(int x, int y) {
	return map[y][x] == 2 ? true : false;
}

bool GameController::isEmpty(int x, int y) {
	return map[y][x] == 0 ? true : false;
}

bool GameController::isWall(glm::vec2 coord) {
	return isWall((int)coord.x, (int)coord.y);
}

bool GameController::isTarget(glm::vec2 coord) {
	return isTarget((int)coord.x, (int)coord.y);
}

bool GameController::isEmpty(glm::vec2 coord) {
	return isEmpty((int)coord.x, (int)coord.y);
}

bool GameController::isMovableCube(glm::vec2 coord) {
	for (int i = 0; i < _movableCubeArray.size(); i++)
	{
		if (_movableCubeArray[i]->coord() == coord)
		{
			return true;
		}
	}
	return false;
}

MovableCube* GameController::findMovableCube(glm::vec2 coord) {
	for (int i = 0; i < _movableCubeArray.size(); i++)
	{
		if (_movableCubeArray[i]->coord() == coord)
		{
			return _movableCubeArray[i];
		}
	}
	return nullptr;
}

void GameController::resetToOrigin() {
	win = false;
	_player->resetToOrigin();
	for (int i = 0; i < _movableCubeArray.size(); i++)
	{
		_movableCubeArray[i]->resetToOrigin();
	}
}

bool GameController::judgeWin() {
	for (int i = 0; i < _movableCubeArray.size(); i++)
	{
		if (!isTarget(_movableCubeArray[i]->coord()))
		{
			return false;
		}
	}
	return true;
}
