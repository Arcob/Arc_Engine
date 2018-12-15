#include "ArcTime.h"

namespace Arc_Engine {
	float ArcTime::_deltaTime = 0.000001f;  // 担心出现除0问题默认为略大于0
	float ArcTime::_fixedDeltaTime = 0.02f;
	float ArcTime::_timeScale = 1.0f; 

	const float ArcTime::deltaTime() {
		return _deltaTime;
	}

	void ArcTime::setDeltaTime(float tempDeltaTime) {
		_deltaTime = tempDeltaTime;
	}
}
