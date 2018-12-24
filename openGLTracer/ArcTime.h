#pragma once

namespace Arc_Engine {

	class ArcTime
	{
	public:
		const static float deltaTime();
		void static setDeltaTime(float tempDeltaTime);

	private:
		static float _deltaTime;
		static float _fixedDeltaTime;  // ������ʱû���ȷ���
		static float _timeScale;  // ������ʱû���ȷ���
	};

}

