#include "MovableObject.h"



/*MovableObject::MovableObject()
{
}


MovableObject::~MovableObject()
{
}*/

void MovableObject::Start() {

}

void MovableObject::Update() {

}

void MovableObject::setTargetCoord(glm::vec2 target) {
	_targetCoord = target;
}

void MovableObject::setPosition(glm::vec2 target) {

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

const bool MovableObject::moving() const {
	return _moving;
}


