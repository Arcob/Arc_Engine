#pragma once
#include "commom.h"
#include "ArcBehaviour.h"
#include "ArcInput.h"
#include "ArcTime.h"


class MovableObject :
	public Arc_Engine::ArcBehaviour
{
public:
	MovableObject()=default;
	virtual ~MovableObject()=default;
	void Start();
	void Update();

	void moveTo(glm::vec2 target);
	void setTargetCoord(glm::vec2 target);
	void setPosition(glm::vec2 target);
	const glm::vec3 getPosition(glm::vec2 vec2);
	void resetToOrigin();
	const glm::vec2 originCoord() const;
	const glm::vec2 coord() const;
	const glm::vec2 targetCoord() const;
	void setCoord(glm::vec2 coord);
	const bool moving() const;


private:
	glm::vec2 _originCoord;
	glm::vec2 _coord;
	glm::vec2 _targetCoord;
	bool _moving = false;
};

