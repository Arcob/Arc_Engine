#pragma once

class ArcBehaviour
{
public:
	//ArcBehaviour(ArcGameObject _gameObject);
	virtual ~ArcBehaviour();
	virtual void Start()=0;
	virtual void Update()=0;
	//const ArcGameObject gameObject() const;

private:
	//ArcGameObject _gameObject;

};

