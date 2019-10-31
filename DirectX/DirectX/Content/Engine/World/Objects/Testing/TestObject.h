#pragma once
#include "../WorldObject.h"



class CTestObject :public CWorldObject
{
	class CCube* Cube;

	float TempRotate{ 0.0f };


public:
	CTestObject(SObjectBase Core);



	virtual void Update() override;

};