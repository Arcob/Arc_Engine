#pragma once
class ArcBehaviour
{
public:
	ArcBehaviour();
	virtual ~ArcBehaviour();
	virtual void Start()=0;
	virtual void Update()=0;
};

