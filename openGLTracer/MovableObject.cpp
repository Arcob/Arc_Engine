#include "MovableObject.h"



/*MovableObject::MovableObject()
{
}


MovableObject::~MovableObject()
{
}*/

void MovableObject::Start() {
	_targetCoord = _coord;
	_originCoord = _coord;
}

void MovableObject::Update() {
	if (glm::distance(gameObject()->transform().position(), getPosition(_targetCoord)) > 0.02f) {
		moveTo(_targetCoord);
	}
	else 
	{
		gameObject()->transformPtr()->setPosition(getPosition(_targetCoord));
		_coord = _targetCoord;
		_moving = false;
	}
}

void MovableObject::moveTo(glm::vec2 target) {
	gameObject()->transformPtr()->setPosition(glm::mix(gameObject()->transform().position(), getPosition(target), GameController::instance->moveSpeed() * Arc_Engine::ArcTime::deltaTime() / glm::distance(gameObject()->transform().position(), getPosition(target))));
}

void MovableObject::setTargetCoord(glm::vec2 target) {
	_targetCoord = target;
	_moving = true;
}

void MovableObject::setPosition(glm::vec2 target) {
	gameObject()->transformPtr()->setPosition(getPosition(target));
}

const glm::vec3 MovableObject::getPosition(glm::vec2 vec2) {
	return glm::vec3(vec2.x, gameObject()->transform().position().y, vec2.y);
}

void MovableObject::resetToOrigin() {
	setPosition(_originCoord);
	_coord = _originCoord;
	_targetCoord = _originCoord;
	_moving = false;
}

const glm::vec2 MovableObject::originCoord() const {
	return _originCoord;
}

const glm::vec2 MovableObject::coord() const{
	return _coord;
}

const glm::vec2 MovableObject::targetCoord() const {
	return _targetCoord;
}

void MovableObject::setCoord(glm::vec2 coord) {
	_coord = coord;
}

const bool MovableObject::moving() const {
	return _moving;
}


