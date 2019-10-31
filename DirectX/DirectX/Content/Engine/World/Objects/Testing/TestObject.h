#pragma once
#include "../WorldObject.h"



class CTestObject :public CWorldObject
{
	class CCube* Cube;



public:
	CTestObject(SObjectBase Core);

};