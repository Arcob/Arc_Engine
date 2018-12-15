#pragma once

namespace Arc_Engine {

	static class ArcTime
	{
	public:
		const static float deltaTime();
		void static setDeltaTime(float tempDeltaTime);

	private:
		static float _deltaTime;
		static float _fixedDeltaTime;  // 这俩暂时没用先放着
		static float _timeScale;  // 这俩暂时没用先放着
	};

}

