#pragma once
#include "ArcGameObject.h"

namespace Arc_Engine {
	class ArcGameObject;

	class ArcBehaviour
	{
	public:
		ArcBehaviour() = default;
		virtual ~ArcBehaviour() = default;
		virtual void Start();
		virtual void Update();
		ArcGameObject* const gameObject() const;
		void setGameObject(ArcGameObject* gameObject);

	private:
		ArcGameObject *_gameObject = nullptr;

	};
}

