#include "GameController.h"




/*GameController::GameController()
{
}


GameController::~GameController()
{
}*/

GameController* GameController::instance = nullptr;

void GameController::Awake()
{
	instance = this;
}

void GameController::Start()
{
	
}

void GameController::Update()
{
	
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

//bool GameController::isMovableCube(glm::vec2 coord);
//MovableCube findMovableCube(Vector2 coord);
//void GameController::resetToOrigin();
//bool GameController::judgeWin();
