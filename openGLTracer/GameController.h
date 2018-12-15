#pragma once
#include "ArcBehaviour.h"
#include <glm/glm.hpp>
#include "ArcInput.h"

class GameController :
	public Arc_Engine::ArcBehaviour
{
public:
	GameController()=default;
	~GameController()=default;
	void Awake();
	void Start();
	void Update();

	const float moveSpeed() const;

	bool isWall(int x, int y);
	bool isTarget(int x, int y);
	bool isEmpty(int x, int y);
	bool isWall(glm::vec2 coord);
	bool isTarget(glm::vec2 coord);
	bool isEmpty(glm::vec2 coord);
	bool isMovableCube(glm::vec2 coord);
	//MovableCube findMovableCube(Vector2 coord);
	void resetToOrigin();
	bool judgeWin();
	
	static GameController* instance;

private:
	//private MovableCube[] MovableCubeArray;
	//private Player player;
	float _moveSpeed = 2.0;
	
	bool win = false;
	int map[7][6] = { //0是空格，1是墙，2是目标点
	{1,1,1,1,1,1},
	{1,0,0,0,0,1},
	{1,0,0,0,0,1},
	{1,2,2,0,1,1},
	{1,0,2,0,1,1},
	{1,0,0,1,1,1},
	{1,1,1,1,1,1},
	};
};

