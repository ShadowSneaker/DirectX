#pragma once
#include "../WorldObject.h"



class CTestObject :public CWorldObject
{
	class CCube* Cube;

	float TempRotate{ 0.0f };


public:
	CTestObject(SObjectBase Core);

	~CTestObject();


	virtual void Update() override;

};