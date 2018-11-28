#pragma once
#include "ArcGameObject.h"

namespace Arc_Engine {
	class ArcGameObject;

	class ArcBehaviour
	{
	public:
		ArcBehaviour();
		virtual ~ArcBehaviour();
		virtual void Start();
		virtual void Update();
		const ArcGameObject* gameObject() const;
		void setGameObject(ArcGameObject* gameObject);

	private:
		ArcGameObject *_gameObject = nullptr;

	};
}

